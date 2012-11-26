/*
 * delete_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef DELETE_FILE_H_
#define DELETE_FILE_H_


/**
 * @brief Delete a file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return Returns an integer value, if the value is > 0 then the file was
 * deleted successfully. If the value is <= 0 then the file failed to delete.
 *
 * @exception FILE_NOT_FOUND If the file at the specified path does
 * not already exist.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_delete(char *pathname);


#endif /* DELETE_FILE_H_ */
