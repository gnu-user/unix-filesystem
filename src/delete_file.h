/*
 * delete_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#ifndef DELETE_FILE_H_
#define DELETE_FILE_H_

/** sfs_delete
 * Delete a file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return an integer value,
 * If the value > 0 then the file was deleted successfully.
 * If the value <= 0 then the file failed to be delete.
 *
 * @exception FILE_NOT_FOUND If the file at the specified path does
 * not already exist
 */
extern int sfs_delete(char *pathname);

#endif /* DELETE_FILE_H_ */
