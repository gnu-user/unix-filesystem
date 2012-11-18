/*
 * system_open_file_table.h
 *
 *  Created on: 2012-11-17
 *      Author: joseph
 */

#include "globdata.h"
#include "index_block.h"
#include "I_node.h"

#ifndef SYSTEM_OPEN_FILE_TABLE_H_
#define SYSTEM_OPEN_FILE_TABLE_H_

/**
 * System wide open file table contains an array of file descriptors that will
 * be open.
 */
typedef struct{
	inode fd[NUMOFL];
} swoft;

extern swoft system_open_tb;
extern int add_to_swoft(location block_num);

#endif /* SYSTEM_OPEN_FILE_TABLE_H_ */
