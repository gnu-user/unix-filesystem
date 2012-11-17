#ifndef I_NODE_H_
#define I_NODE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct{
	char name[7];
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
#endif /* I_NODE_H_ */
