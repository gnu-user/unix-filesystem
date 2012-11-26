/*
 * close_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */
#include "error.h"

#ifndef CLOSE_FILE_H_
#define CLOSE_FILE_H_


/**
 * @brief Closes the file, which indicates that the file is no longer needed.
 *
 * @param fd A file descriptor for the file to close.
 *
 * @return Returns an integer value. If the value is > 0 the file
 * close was a success, if the value <= 0 the file close was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_close(int fd);


#endif /* CLOSE_FILE_H_ */
