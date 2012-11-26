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
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_gettype(char *pathname);


#endif /* GET_TYPE_H_ */
