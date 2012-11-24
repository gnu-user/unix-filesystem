#include "glob_data.h"
#include "glob_func.h"
#include "index_block.h"
#include <stdbool.h>
#include "../lib/uuid/uuid.h"

#ifndef I_NODE_H_
#define I_NODE_H_

typedef struct{
	char name[MAX_NAME_LEN];
	bool type;
	bool read;
	bool write;
	bool execute;
	uint32_t date_of_create;
	uint32_t date_last_accessed;
	uint32_t date_last_modified;
	uint32_t file_owner;
	uint32_t last_user_modified;
	uint16_t file_size; 				//Might need to be unsigned
	uint32_t location;					//Addreglob_datass of the index block
	bool encrypted;
	uint32_t check_sum;
	uuid_t uuid;
} inode;

/**
 * Get an inode set to null state
 *
 * @return the null inode
 */
extern inode get_null_inode();

/**
 * Get the I_node given the block index of the Inode
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return inode pointer of the Inode at the given location.
 * If Inode is null the Inode was not found.
 */
extern inode* get_inode(uint32_t block_num);

/**
 * Get the inode's uuid
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return a pointer to the uuid
 */
extern unsigned char* get_uuid(uint32_t block_num);

/**
 * Get the index block from the Inode given the location of the Inode
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return index integer
 * If index >= 0 then the function was successful,
 * if index < 0 then the function was unsuccessful
 */
extern uint32_t get_index_block(uint32_t block_num);

/**
 * Get the type of the inode, whether it is a directory or a file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return the type of the file
 * If type = 1 then the Inode is for a directory,
 * if type = 0 then the Inode is for a file,
 * otherwise the function has failed.
 */
extern int get_type(uint32_t block_num);

/**
 * Get size of the file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return the size of the file
 * if the size >= 0 then the function was successful
 * if the size < 0 then the function was unsuccessful
 */
extern uint32_t get_size(uint32_t block_num);

/**
 * Check if the file is encrypted
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return whether the file is encrypted
 * if encrypt is 0 then the file is not encrypted
 * if encrypt is 1 then the file is encrypted
 * otherwise the function was unsuccessful
 */
extern int get_encrypted(uint32_t block_num);

/**
 * Get the name of the file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return a char pointer to the file's name
 * if the file's name = NULL then the function was unsuccessful
 */
extern char* get_name(uint32_t block_num);

/**
 * Get the checksum of the data
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return the checksum, null if fail
 */
extern uint32_t get_crc(uint32_t block_num);

/*
 * Traverses the index of a directory and returns the location of the inode with
 * the name that matches the request. If the inode is found in the index then the
 * location of the inode is returned, otherwise if it is not found NULL is returned.
 *
 * @pre index_blocks MUST be a NULL terminated
 *
 * @param locations A NULL terminated array of index block locations
 * @param name The name of the file/directory
 *
 * @return The location of the inode with a name that matches the request, NULL if
 * not found
 *
 */
extern uint32_t find_inode(locations index_blocks, char* name);

/**
 * Link the inode to the parent
 *
 * @param the parent's location
 * @param the child inode's location
 *
 * @return the error message
 * if value >= 0 success
 * if value < 0 failure
 */
extern int link_inode_to_parent(uint32_t parent_location, uint32_t inode_location);

/**
 * Unlink the child's inode from the parent's index block
 *
 * @param the parent's location
 * @param the child inode's location
 *
 * @return the error message
 * if value >= 0 success
 * if value < 0 failure
 */
extern int unlink_inode_from_parent(uint32_t parent_location, uint32_t inode_location);


#endif /* I_NODE_H_ */
