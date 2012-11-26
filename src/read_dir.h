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

#ifndef READ_DIR_H_
#define READ_DIR_H_

/**
 * @brief List the contents of a directory.
 *
 * @details Reads the file name components from a directory file.
 * This is done by reading in all the locations from within a
 * directory file's index structure and analyzing the inodes at each
 * location.
 * The first time sfs_readdir is called, the first file name component
 * in the directory will be placed into memory at the location pointed
 * to by mem_pointer. Each successive call to sfs_readdir will place
 * the next name component from the directory into the mem_pointer
 * buffer. When all names have been returned, sfs_readdir will place
 * nothing in the buffer, and return a value of zero to indicate the
 * directory has been completely scanned.
 *
 * @param fd A file descriptor for the file to read data from.
 *
 * @param mem_pointer The memory location to store the file name components.
 *
 * @return Returns an integer value. If the value > 0 reading the directory
 * was successful. If the value = 0, there is nothing contents in the
 * directory. If the value < 0 the directory read operation was unsuccessful.
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_readdir(int fd, char *mem_pointer);


#endif /* READ_DIR_H_ */
