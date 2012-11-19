#ifndef I_NODE_H_
#define I_NODE_H_

#include "glob_data.h"
#include <stdint.h>
#include <stdbool.h>

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

extern inode* get_inode(int block_num);

extern int get_index_block(int block_num);

extern int get_type(int block_num);

extern int get_size(int block_num);

extern int get_encrypted(int block_num);

extern char* get_name(int block_num);

/*
 * Traverses the index of a directory and returns the location of the inode with
 * the name that matches the request. If the inode is found in the index then the
 * location of the inode is returned, otherwise if it is not found NULL is returned.
 *
 * @note The function only searches one directory index at a time, if a directory contains
 * many files and thus multiple indexes, you must call find_inode for EACH index.
 *
 * @param location The location of the directory index
 * @param name The name of the file/directory
 * @return The location of the inode with a name that matches the request
 *
 */
uint32_t find_inode(uint32_t location, char* name);


#endif /* I_NODE_H_ */
