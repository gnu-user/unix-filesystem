/*
 * open_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef OPEN_FILE_H_
#define OPEN_FILE_H_

/** sfs_open
 * Opens the file specified by the pathname, if the file is successfully opened
 * a file descriptor is returned.
 *
 * @param pathname The full pathname of a file
 *
 * @return A file descriptor for the file opened
 * If the fd >= 0 then the file has successfully opened.
 * If the fd < 0 then the file has failed to open.
 *
 * @exception FILE_NOT_FOUND If the file specified in pathname does not exist
 */
extern int sfs_open(char *pathname);

/**
 * The all of the information stored in the given file descriptor's Inode.
 *
 * @param fd integer, the file descriptor.
 *
 * @return an integer value, Adjusted to output the fd if success to allow for
 * it to be used on the return line
 * if the value >= 0 then the function is successful
 * if the value < 0 then the function is unsuccessful
 */
extern int show_information(int fd);

#endif /* OPEN_FILE_H_ */
