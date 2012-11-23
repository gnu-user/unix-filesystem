#include "I_node.h"

#ifndef SYSTEM_OPEN_FILE_TABLE_H_
#define SYSTEM_OPEN_FILE_TABLE_H_

/**
 * System wide open file table contains an array of file descriptors that will
 * be open.
 *
 * Needs to have at least 5 instances (to have 5 files open at once)
 */
typedef struct{
	inode fd[NUMOFL];
	bool taken[NUMOFL];
} swoft;

extern swoft system_open_tb;
extern int add_to_swoft(uint32_t block_num);

/**
 * validate whether the fd is a valid fd in the swoft
 */
extern int validate_fd(int fd);

extern inode get_swoft_inode(fd);

/**
 * Find all entries in the swoft of the given file with the given checksum
 * @param file_name the file name
 * @param crc the checksum to validate unique inode
 *
 * @return an integer value
 * if value = 1 success
 * otherwise fail
 */
extern int find_and_remove(char* file_name, uint32_t crc);

#endif /* SYSTEM_OPEN_FILE_TABLE_H_ */
