/*
 * open_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef OPEN_FILE_H_
#define OPEN_FILE_H_


/**
 * @brief Opens the file specified by the pathname, if the file is
 * successfully opened a file descriptor is returned.
 *
 * @details Since file descriptors are simply copies of inodes,
 * this function traverses the specified path and attempts to find
 * the inode with a name that matches the one specified in the path.
 * This is done by traversing the index blocks at each token in the
 * path specified, and checking the name of the path token against
 * the inodes at each location specified by the index. Once the
 * inode with the name matching the final path token has been
 * found, the inode pseudo-object returned is added to the
 * system-wide open file table.
 *
 * @param pathname The full pathname of a file.
 *
 * @return Returns a file descriptor for the file opened.
 * If the fd >= 0 then the file has successfully opened.
 * If the fd < 0 then the file has failed to open.
 *
 * @exception FILE_NOT_FOUND If the file at the specified path
 * does not exist.
 *
 * @exception INVALID_PATH If the specified path is invalid.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_open(char *pathname);


/**
 * @brief Show all of the information stored in the given file descriptor.
 *
 * @details Since file descriptors are simply inode pseudo-objects, this
 * function simply prints the attributes associated with an inode's defined
 * data structure.
 *
 * @param fd integer, the file descriptor.
 *
 * @return Returns an integer value. The function is adjusted to
 * output the file descriptor if the file descriptor is retrieved
 * successfully, to allow for it to be used on the return line.
 * If the value returned is >= 0 then the function successfully
 * retrieved a file descriptor. If the value < 0 then the
 * function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int show_information(int fd);


#endif /* OPEN_FILE_H_ */
