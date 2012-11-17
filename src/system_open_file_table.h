/*
 * system_open_file_table.h
 *
 *  Created on: 2012-11-17
 *      Author: joseph
 */

#include "globdata.h"
//#include "I_node.h"

#ifndef SYSTEM_OPEN_FILE_TABLE_H_
#define SYSTEM_OPEN_FILE_TABLE_H_

/**
 * System wide open file table contains an array of file descriptors that will
 * be open.
 */
typedef struct{
	inode fd[NUMOFL];
} swoft;

#endif /* SYSTEM_OPEN_FILE_TABLE_H_ */
