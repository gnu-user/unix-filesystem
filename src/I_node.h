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
 * @brief Contains the data stored in inodes.
 *
 * @details This struct defines the data which will be stored inside blocks designated as inodes on the disk.
 * In particular, inodes store data pertaining to the attributes of they files they represent, as well
 * as linkages to the index block structure that allows the file system to track their
 * associated data blocks. Since files can be either a directory or a data file, inodes
 * provide all the data required to track both types of data structures.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
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
 * @brief Holds the current working directory data.
 *
 * @details This struct holds the current working directory in memory. It is used in a pseudo-object oriented
 * fashion in order to encapsulate the data pertaining to the contents of the current working directory
 * and the last directory element that was retrieved from reading the directory contents.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
typedef struct
{
	inode directory;					/** This contains the inode for the current working directory. */
	uint32_t cur_index;					/** This tracks the amount of times the directory contents have been returned, in order to iterate through the entire directory contents. */
} cwd;

/**
 * @var cur_dir
 *
 * @brief This variable is used to store a static instance of the cwd struct.
 */
static cwd cur_dir;


/**
 * @brief Get an inode set to null state.
 *
 * @details This function generates a single block of null-initialized data using the predefined BLKSIZE constant.
 * It then outputs it as type inode.
 *
 * @return Returns a null-initialized inode data structure.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern inode get_null_inode();


/**
 * @brief Get the contents of an inode given its location on disk.
 *
 * @details This function retrieves an inode given its location by retrieving
 * the block and analyzing the contents based on the defined inode data structure.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the inode at the given location.
 * If the returned value is NULL, an inode was not found at the specified location.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern inode* get_inode(uint32_t block_num);


/**
 * @brief Get an inode's UUID given its location on disk.
 *
 * @details This function retrieves a UUID from an inode by retrieving the block
 * and analyzing the contents based on the defined inode data structure.
 * UUIDs are human-readable strings, therefore the return type for this operation
 * is an array of characters.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the UUID from within the inode at the given location.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern unsigned char* get_uuid(uint32_t block_num);


/**
 * @brief Get the index block which an inode links to given the inode's location on disk.
 *
 * @details This function retrieves the first index block location from an inode by retrieving the block
 * and analyzing the contents based on the defined inode data structure.
 * This allows the inode to be associated with its index block data structure, which in turn allows
 * for the retrieval of all the data blocks associated with the file.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the location of the index block on disk.
 * If index >= 0 then the function was successful, if index < 0 then
 * the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_index_block(uint32_t block_num);


/**
 * @brief Get the type of file from an inode, whether it is a directory or a data file.
 *
 * @details This function retrieves the file type attribute from an inode by retrieving the block
 * and analyzing the contents based on the defined inode data structure. This allows for the
 * file system to determine whether an inode is for a data file or a directory.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the type of the file.
 * If the function returns 1, then the inode is for a directory,
 * if the function returns 0, then the inode is for a data file,
 * Otherwise retrieving the type was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int get_type(uint32_t block_num);


/**
 * @brief Get size of a file given its inode's location on disk.
 *
 * @details This function retrieves the file size attribute from an inode by retrieving the block
 * and analyzing the contents based on the defined inode data structure. This allows for the file
 * system to quickly retrieve the size of the data (in bytes) stored within a file's data blocks.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns the size of the data blocks' contents for the file in bytes.
 * If the returned size >= 0, then the function was successful,
 * if the returned size < 0, then the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_size(uint32_t block_num);


/**
 * @brief Check if the specified file is encrypted given its inode's location on disk.
 *
 * @details This function checks whether a file's data blocks are encrypted by retrieving
 * the inode and analyzing the contents based on the defined inode data structure. This
 * allows for the file system to determine whether to decrypt the data blocks associated
 * with the file before reading, or whether they are aren't encrypted and can
 * be read normally.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns whether the file is encrypted.
 * If the returned value is 0 then the file is not encrypted and
 * if it is 1 then the file is encrypted. Otherwise,
 * the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int get_encrypted(uint32_t block_num);


/**
 * @brief Get the name of the file given its inode's location on disk.
 *
 * @details This function determines the human-readable name of a file by
 * retrieving the inode and analyzing the contents based on the defined inode
 * data structure. The name is a human-readable string.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the file's name, which is a string.
 * If the function returns NULL, then the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern char* get_name(uint32_t block_num);


/**
 * @brief Get the encryption checksum of a file given its inode's location on disk.
 *
 * @details This function retrieves the encryption checksum for a file's data
 * blocks, so that it can be determined whether the encryption and decryption process
 * was completed successfully. This is done by retrieving the inode and analyzing
 * the contents based on the defined inode data structure.
 *
 * @param block_num The block location of the inode on disk.
 *
 * @return Returns a pointer to the checksum, which is a string.
 * If the function returns NULL, then the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_crc(uint32_t block_num);


/*
 * @brief Traverses the index structure of a directory and returns the location of the inode with
 * the name that matches the request.
 *
 * @details This function works by analyzing a series of index block locations, retrieving
 * the inodes located there, and checking the name stored within the defined inode data
 * structure. The requested name is matched against this attribute for each inode in the
 * index data structure, until there are no more locations in the index.
 *
 * @pre index_blocks MUST be a NULL terminated array of locations.
 *
 * @param locations A NULL terminated array of index block locations.
 *
 * @param name The name of the file/directory to search for.
 *
 * @return Returns the location of the inode with a name that matches the request.
 * If the inode is found in the index then the location of the inode is returned.
 * If it is not found, NULL is returned.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t find_inode(locations index_blocks, char* name);


/**
 * @brief Links the inode to a parent's index structure.
 *
 * @detail This function works by accessing the specified parent inode, and
 * accessing the index data structure that it links to within its defined inode
 * data structure. After accessing this index structure, the specified child
 * inode is appended to the index. The index is rebuilt and written to disk,
 * and the newly created index is linked to within the parent's inode. This
 * inode is then rewritten at the original location, overwriting the old one.
 * Upon completion of this operation the old index blocks are freed. If a
 * failure occurs during this operation, the changes are automatically
 * undone. The internal implementation of this function utilizes
 * copy-on-write journalling in order to prevent any damage to the file
 * system from failed operations.
 *
 * @param parent_location The parent's location on disk.
 *
 * @param inode_location The child inode's location on disk.
 *
 * @return Returns a value to signify success or failure. If the value is >= 0
 * the function was successful. If value is < 0, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int link_inode_to_parent(uint32_t parent_location, uint32_t inode_location);


/**
 * @brief Unlinks a child's inode from the parent's index structure.
 *
 * @details This function works by accessing the specified parent inode, and
 * accessing the index data structure that it links to within its defined inode
 * data structure. After accessing this index structure, the block at
 * each indexed location is loaded and the name attribute within the inode
 * at that block is checked against the name within the specified child inode.
 * Once a match is found, the corresponding indexed block is removed from the
 * index structure. The index is rebuilt and written to disk,
 * and the newly created index is linked to within the parent's inode. This
 * inode is then rewritten at the original location, overwriting the old one.
 * Upon completion of this operation the old index blocks are freed. If a
 * failure occurs during this operation, the changes are automatically
 * undone. The internal implementation of this function utilizes
 * copy-on-write journalling in order to prevent any damage to the file
 * system from failed operations.
 *
 * @param parent_location The parent's location on disk.
 *
 * @param inode_location The child inode's location on disk.
 *
 * @return Returns a value to signify success or failure. If the value is >= 0
 * the function was successful. If value is < 0, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int unlink_inode_from_parent(uint32_t parent_location, uint32_t inode_location);


/**
 * @brief Gets the next entry for the current directory and increments the index of the last
 * accessed item within a directory.
 *
 * @details This function is used when reading directories. Directory elements are retrieved
 * from an index data structure that corresponds with a directory's inode. Each of these
 * elements must be iterated through in order to fully traverse a directory's contents.
 * After the entire directory contents are traversed, the function returns a zero value.
 * If the contents are traversed again, the function restarts from the beginning.
 *
 * @param directory The inode of the current directory.
 *
 * @return Returns the directory element.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int get_index_entry(inode directory);


/**
 * @brief Resets the index entry count. Attempting to get the next directory item after this
 * function has executed will get the first item in the directory.
 *
 * @details This function is used to reset the iterator for traversing the contents of
 * a directory structure. After this function is called, any further attempts at traversing
 * the contents of a directory will start over again from the first element.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern void reset_index_entry();


#endif /* I_NODE_H_ */
