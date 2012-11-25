/*
 * get_type.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#ifndef GET_TYPE_H_
#define GET_TYPE_H_

/** sfs_gettype
 * Get the type of the file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return the file type of the given file
 * If the file type >= 0 then the file type retrieval is a success
 * 	If the file type is 0, or 1 then it is a file, directory respectively
 * 	If the file type > 1 then the file is not known
 * If the file type < 0 then the file type retrieval has failed
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_gettype(char *pathname);

#endif /* GET_TYPE_H_ */
