#include "glob_data.h"
#include "index_block.h"
#include <stdbool.h>

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
	uint32_t location;					//Address of the index block
	bool encrypted;
	uint32_t check_sum;
} inode;

extern inode get_null_inode();

extern inode* get_inode(int block_num);

extern uint32_t get_index_block(int block_num);

extern int get_type(int block_num);

extern int get_size(int block_num);

extern int get_encrypted(int block_num);

extern char* get_name(int block_num);

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
uint32_t find_inode(locations index_blocks, char* name);


#endif /* I_NODE_H_ */
