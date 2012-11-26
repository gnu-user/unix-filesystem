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


#include "blockio.h"
#include "glob_data.h"
#include "error.h"

#ifndef BLOCK_FUNC_H_
#define BLOCK_FUNC_H_


/**
 * @brief A wrapper for the put_block function.
 *
 * @param location The location on disk for the buffer to be written to.
 *
 * @param The buffer to store on disk.
 *
 * @return Returns an integer value. If the value >= 0, the function
 * was successful. Otherwise, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int write_block(uint32_t location, byte* buf);


/**
 * @brief A wrapper for the get_block function.
 *
 * @param location The location on disk for the buffer to be written to.
 *
 * @param The buffer to store on disk.
 *
 * @return Returns an integer value. If the value >= 0 the function
 * was successful. Otherwise, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int read_block(uint32_t location, byte* buf);


/**
 * @brief Get the data blocks and concatenate them into a large byte buffer.
 *
 * @param location The locations of the data blocks on disk.
 *
 * @return Returns the data_buffer containing all of the bytes of data.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern byte* get_data(locations location);

#endif /* BLOCK_FUNC_H_ */
