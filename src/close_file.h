/*
 * close_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#ifndef CLOSE_FILE_H_
#define CLOSE_FILE_H_

/** sfs_close
 * Closes the file, which indicates that the file is no longer needed
 *
 * @param fd A file descriptor for the file to close
 *
 * @return a integer value
 * If the value > 0 the file close was a success
 * If the value <= 0 the file close was unsuccessful
 */
int sfs_close(int fd);

#endif /* CLOSE_FILE_H_ */
