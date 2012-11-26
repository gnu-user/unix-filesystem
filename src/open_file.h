/*
 * SneakyFS - A Secure UNIX File System
 *
 * Copyright (C) 2012, Jonathan Gillett, Joseph Heron, and Daniel Smullen
 * All rights reserved.
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
 * @author Jonathan Gillett
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
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int show_information(int fd);


#endif /* OPEN_FILE_H_ */
