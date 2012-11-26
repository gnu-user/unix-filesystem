/*
 * read_dir.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef READ_DIR_H_
#define READ_DIR_H_

/** sfs_readdir
 * Reads the file name components from a directory file. The first time
 * sfs_readdir is called, the first file name component in the directory will be
 * placed into memory at the location pointed to by mem_pointer. Each successive
 * call to sfs_readdir will place the next name component from the directory into
 * the mem_pointer buffer. When all names have been returned, sfs_readdir will
 * place nothing in the buffer, and return a value of zero to indicate the
 * directory has been completely scanned.
 *
 * @param fd A file descriptor for the file to read data from
 * @param mem_pointer The memory location to store the file name components
 *
 * @return an integer value
 * If the value > 0 the read dir was a success
 * If the value = 0 if there is no contents in dir
 * If the value < 0 the read dir was unsuccessful
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 */
extern int sfs_readdir(int fd, char *mem_pointer);

#endif /* READ_DIR_H_ */
