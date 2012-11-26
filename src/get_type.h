/*
 * get_type.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef GET_TYPE_H_
#define GET_TYPE_H_


/**
 * @brief Get the type of the file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path.
 *
 * @return Returns the file type of the given file. If the file type >= 0
 * then the file type retrieval was a success.If the file type is 0, or 1
 * then it is a file, or directory respectively. If the file type > 1 then
 * the file type is not known. If the file type < 0 then the file
 * type retrieval failed.
 *
 * @exception FILE_NOT_FOUND If the file at the specified path does not exist.
 *
 * @exception INVALID_PATH If the specified path is invalid.
 */
extern int sfs_gettype(char *pathname);


#endif /* GET_TYPE_H_ */
