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


#include "glob_data.h"
#include "super_block.h"
#include "error.h"

#ifndef MOUNT_H_
#define MOUNT_H_


/**
 * @brief Attempt to mount the filesystem on disk.
 *
 * @details This funcion calls validation methods to
 * ensure that the mount is possible, and file system
 * isn't corrupted. It verifies that the unique
 * identifiers and checksums associated with the various
 * structures on disk are valid and in working order.
 *
 * @return Returns an integer value, if value = 1 the
 * file system has passed validation. If value = -1
 * the file system has failed to validate and should
 * be reinitialized.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int mount(void);


/**
 * @brief Validate the super block on the disk.
 *
 * @details This function determines the integrity of
 * the super block data by validating its unique
 * identifier and checksum.
 *
 * @return Returns an integer value. If value = 1 the
 * super block has passed validation. If the value = -1,
 * the super block has failed validation and should be
 * reinitialized.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int validate_super_block(void);


/* TODO fix seg fault error if the root directory was not written/was overwritten*/
/**
 * @brief Validate that there is a root directory on the disk.
 *
 * @details This function checks the location for the root directory
 * on disk specified by the super block, and determines if the file
 * at that location is valid.
 *
 * @return Returns an integer value, if value = 1 the root directory
 * structure which exists on disk passed validation. If value = -1,
 * the structure failed validation.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int validate_root_dir(void);


#endif /* MOUNT_H_ */
