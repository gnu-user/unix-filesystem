#include "glob_data.h"
#include "glob_func.h"
#include "index_block.h"
#include "error.h"
#include <stdbool.h>
#include "../lib/uuid/uuid.h"

#ifndef I_NODE_H_
#define I_NODE_H_

/**
 * @struct inode
 *
 * This struct defines the data which will be stored inside blocks designated as inodes on the disk.
 * In particular, inodes store data pertaining to the attributes of they files they represent, as well
 * as linkages to the index block structure that allows the file system to track their
 * associated data blocks. Since files can be either a directory or a data file, inodes
 * provide all the data required to track both types of data structures.
 */
typedef struct{
	char name[MAX_NAME_LEN]; 			/** The human-readable name of the file. */
	bool type;							/** The type of file. Files can be either data files, or directories. */
	bool read;							/** This flags whether the file is marked as readable or not. */
	bool write;							/** This flags whether the file is marked as writable or not. */
	bool execute;						/** This flags whether the file is marked as executable or not. */
	uint32_t date_of_create;			/** This stores what the date of creation is for the file. */
	uint32_t date_last_accessed;		/** This stores the date that the file was last accessed by the file system. */
	uint32_t date_last_modified;		/** This stores the date that the file was last modified by the file system. */
	uint32_t file_owner;				/** This stores the name of the owner of the file. */
	uint32_t last_user_modified;		/** This stores the name of the last user who modified the file. */
	uint32_t file_size; 				/** This stores the size of the file in bytes. */
	uint32_t location;					/** This stores the location of the file's first index block on disk. */
	bool encrypted;						/** This flags whether the file's data contents are encrypted. */
	uint32_t check_sum;					/** This stores the encryption checksum for the file, to determine whether it has been encrypted or unencrypted correctly. */
	uuid_t uuid;						/** This stores the universal unique identifier for the file. */
} inode;

/**
 * @struct cwd
 *
 * This struct holds the current working directory in memory. It is used in a pseudo-object oriented
 * fashion in order to encapsulate the data pertaining to the contents of the current working directory
 * and the last directory element that was retrieved from reading the directory contents.
 */
typedef struct
{
	inode directory;					/** This contains the inode for the current working directory. */
	uint32_t cur_index;					/** This tracks the amount of times the directory contents have been returned, in order to iterate through the entire directory contents. */
} cwd;

static cwd cur_dir;

/**
 * Get an inode set to null state.
 *
 * @return Returns a null-initialized inode data structure.
 */
extern inode get_null_inode();

/**
 * Get the contents of an inode given its location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the inode at the given location.
 * If the returned value is NULL, an inode was not found at the specified location.
 */
extern inode* get_inode(uint32_t block_num);

/**
 * Get an inode's UUID given its location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the UUID from within the inode at the given location.
 */
extern unsigned char* get_uuid(uint32_t block_num);

/**
 * Get the index block which an inode links to given the inode's location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the location of the index block on disk.
 * If index >= 0 then the function was successful,
 * if index < 0 then the function was unsuccessful.
 */
extern uint32_t get_index_block(uint32_t block_num);

/**
 * Get the type of file from an inode, whether it is a directory or a data file.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the type of the file.
 * If the function returns 1, then the inode is for a directory,
 * if the function returns 0, then the inode is for a data file,
 * Otherwise the function has failed.
 */
extern int get_type(uint32_t block_num);

/**
 * Get size of a file given its inode's location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the size of the data blocks' contents for the file in bytes.
 * If the returned size >= 0, then the function was successful,
 * if the returned size < 0, then the function was unsuccessful.
 */
extern uint32_t get_size(uint32_t block_num);

/**
 * Check if the specified file is encrypted given its inode's location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns whether the file is encrypted.
 * If the returned value is 0 then the file is not encrypted and
 * if it is 1 then the file is encrypted. Otherwise,
 * the function was unsuccessful.
 */
extern int get_encrypted(uint32_t block_num);

/**
 * Get the name of the file given its inode's location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the file's name, which is a string.
 * If the function returns NULL, then the function was unsuccessful.
 */
extern char* get_name(uint32_t block_num);

/**
 * Get the encryption checksum of a file given its inode's location on disk.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the checksum, which is a string.
 * If the function returns NULL, then the function was unsuccessful.
 */
extern uint32_t get_crc(uint32_t block_num);

/*
 * Traverses the index structure of a directory and returns the location of the inode with
 * the name that matches the request.
 *
 * @pre index_blocks MUST be a NULL terminated array of locations.
 *
 * @param locations A NULL terminated array of index block locations.
 * @param name The name of the file/directory to search for.
 *
 * @return Returns the location of the inode with a name that matches the request.
 * If the inode is found in the index then the location of the inode is returned.
 * If it is not found, NULL is returned.
 */
extern uint32_t find_inode(locations index_blocks, char* name);

/**
 * Links the inode to a parent's index structure.
 *
 * @param parent_location The parent's location on disk.
 * @param inode_location The child inode's location on disk.
 *
 * @return Returns a value to signify success or failure. If the value is >= 0
 * the function was successful. If value is < 0, the function was unsuccessful.
 */
extern int link_inode_to_parent(uint32_t parent_location, uint32_t inode_location);

/**
 * Unlinks a child's inode from the parent's index structure.
 *
 * @param parent_location The parent's location on disk.
 * @param inode_location The child inode's location on disk.
 *
 * @return Returns a value to signify success or failure. If the value is >= 0
 * the function was successful. If value is < 0, the function was unsuccessful.
 */
extern int unlink_inode_from_parent(uint32_t parent_location, uint32_t inode_location);

/**
 * Gets the next entry for the current directory and increments the index of the last
 * accessed item within a directory.
 *
 * @param directory The inode of the current directory.
 *
 * @return Returns the directory element.
 */
extern int get_index_entry(inode directory);

/**
 * Resets the index entry count. Attempting to get the next directory item after this
 * function has executed will get the first item in the directory.
 */
extern void reset_index_entry();


#endif /* I_NODE_H_ */
