/*
 * get_size.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#ifndef GET_SIZE_H_
#define GET_SIZE_H_

/** sfs_getsize
 * Get the size (in blocks) of the file with the pathname specified.
 *
 * @param pathname The pathname of the file or directory, must be full directory
 * path
 * If it is a file then the size of the file will be returned
 * If it is a directory the number of entries will be returned
 *
 * @return the size of the given file
 * If the value < 0 then an error has occurred.
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_getsize(char *pathname);

#endif /* GET_SIZE_H_ */
