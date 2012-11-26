/*
 * create_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef CREATE_FILE_H_
#define CREATE_FILE_H_


/**
 * @brief Creates a new file or directory at the path specified.
 *
 * @details Create a file with the pathname specified. If there
 * is not already a file with the same pathname, the pathname
 * must contain the full directory path. The parameter type
 * specifies whether a regular file or a directory file should be
 * created.
 *
 * @param pathname The pathname of file to create, it must be
 * a full directory path.
 *
 * @param type The type of file to create, zero for a regular
 * file, one for a directory.
 *
 * @return Returns an integer value. If the value > 0 the
 * file creation was a success, and if the value <= 0 the
 * file createion was unsuccessful.
 *
 * @exception INVALID_FILE_NAME If the specified file name is already in use.
 *
 * @exception INVALID_FILE_TYPE If the file type specified is not a regular file
 * (0) or a directory file (1).
 *
 * @exception INVALID_PATH If the pathname specified does not already exist.
 *
 * @exception INSUFFICIENT_DISK_SPACE If the length of the blocks to be written
 * is greater than the amount of available blocks on disk.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_create(char *pathname, int type);


#endif /* CREATE_FILE_H_ */
