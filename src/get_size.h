/*
 * get_size.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef GET_SIZE_H_
#define GET_SIZE_H_


/**
 * @brief Get the size (in blocks) of the file with the pathname specified.
 *
 * @details Traverses the index block structure of a given file, reads all
 * the locations inside, and the number of blocks is returned. If the file is a
 * data file, the size of the file is returned. If the file is a directory,
 * the number of elements within the directory will be returned.
 *
 * @param pathname The pathname of the file or directory, must be full directory
 * path. Relative paths are not accepted.
 *
 * @return Returns the size of the given file. If the value < 0 then
 * an error occurred.
 *
 * @exception FILE_NOT_FOUND If the file at the given pathname does not exist.
 *
 * @exception INVALID_PATH If if the path specified is invalid, incomplete,
 * or does not exist.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_getsize(char *pathname);


#endif /* GET_SIZE_H_ */
