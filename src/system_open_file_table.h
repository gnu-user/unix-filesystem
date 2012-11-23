#include "I_node.h"
#include "../lib/uuid/uuid.h"

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

/**
 * Add the inode to the swoft
 *
 * @param block_num location, the Inode's location on disk
 *
 * @param an integer value,
 * if the value >= 0 then the inode was found and added to the swoft
 * if the value == -1 then the swoft was full
 * if the value == -2 then the inode was not found
 * otherwise the function was unsuccessful
 */
extern int add_to_swoft(uint32_t block_num);

/**
 * validate whether the fd is a valid fd in the swoft
 *
 * @param the file descriptor
 *
 * @return an integer value,
 * if value >= 0 success
 * otherwise failure
 */
extern int validate_fd(int fd);

/**
 * Get the inode from the swoft
 *
 * @param the file descriptor
 *
 * @return the inode from the swoft given the file descriptor
 */
extern inode get_swoft_inode(fd);

/**
 * remove the fd from the swoft
 *
 * @param the file descriptor to remove
 */
extern void remove_fd(int fd);

/**
 * Find all entries in the swoft of the given file with the given checksum
 * @param file_name the file name
 * @param uuid the uuid to validate unique inode
 *
 * @return an integer value
 * if value = 1 success
 * otherwise fail
 */
extern int find_and_remove(char* file_name, uuid_t uuid);

#endif /* SYSTEM_OPEN_FILE_TABLE_H_ */
