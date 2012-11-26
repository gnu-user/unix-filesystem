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
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_getsize(char *pathname);


#endif /* GET_SIZE_H_ */
