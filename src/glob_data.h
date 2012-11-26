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


#include <stdint.h>
#include <stdlib.h>

#ifndef GLOBDATA_H_
#define GLOBDATA_H_


/**
 * @define MAX_IO_LENGTH
 *
 * @brief Defines the maximum length of any input or output buffer
 * in the test interface for the file system.
 *
 * @details This is the maximum number of bytes that can be read from or
 * written to a file with a single file system call using this program.
 * Since files are limited to 512 bytes length, this should be
 * sufficient. The format definition is necessary because
 * macro substitutions do not take place within quoted strings.
 * The maximum length is defined as 1024 bytes.
 */
#define MAX_IO_LENGTH   1024


/**
 * @define IO_BUF_FORMAT
 *
 * @brief Defines the format of the input/output buffer.
 */
#define IO_BUF_FORMAT   "%512s"


/**
 * @define MAX_INPUT_LENGTH
 *
 * @brief This is the maximum length of input strings (e.g., file names) read from
 * the standard input. This should be large enough for most purposes.
 * the format definition is necessary because macro substitutions
 * do not take place within quoted strings.
 */
#define MAX_INPUT_LENGTH  512


/**
 * @define INPUT_BUF_FORMAT
 *
 * @brief Defines the format of the input buffer.
 */
#define INPUT_BUF_FORMAT  "%1024s"

/**
 * @define UNIT_TESTING
 *
 * @brief Define if we are doing unit testing instead of executing sfs_test.
 *
 * @deprecated This definition is no longer used since the unit test suite
 * was no longer used and deprecated once the high-level file system functions
 * were implemented.
 */
//#define UNIT_TESTING


/**
 * @define BLKSIZE
 *
 * @brief The size of blocks on the simulated disk.
 */
#define BLKSIZE  128


/**
 * @define NUMBLKS
 *
 * @brief The number of blocks on simulated disk.
 */
#define NUMBLKS  512


/**
 * @define NUMOFL
 *
 * @brief The number of files that can be open at once. Determines
 * the size of the system-wide open file table.
 */
#define NUMOFL	  32


/**
 * @define MAX_NAME_LEN
 *
 * @brief The maximum length of a component in a pathname including the NULL terminator.
 */
#define MAX_NAME_LEN 7


/**
 * @define SUPER_BLOCK
 *
 * @brief Determines the default location of the super block on disk.
 */
#define SUPER_BLOCK	 0


/**
 * @define FBL_INDEX
 *
 * @brief Determines the default location of the free block list's
 * index data structure.
 */
#define FBL_INDEX 1


/**
 * @var FBL_DATA_SIZE
 *
 * @brief The size of the free block list data blocks, not including the
 * overhead of the size of each index block needed to index the
 * free block list data blocks.
 */
extern uint32_t FBL_DATA_SIZE;


/**
 * @var FBL_TOTAL_SIZE
 *
 * @brief The total size of the free block list data blocks, including
 * the overhead of the size of each index block needed to index the
 * free block list data blocks.
 */
extern uint32_t FBL_TOTAL_SIZE;


/**
 * @var ROOT
 *
 * @brief The default location for the root directory's inode.
 */
extern uint32_t ROOT;


/**
 * @typedef byte
 *
 * @brief A byte is defined as an 8-bit unsigned integer.
 */
typedef uint8_t byte;


/**
 * @typedef block
 *
 * @brief A block is defined as an array of bytes, with each element
 * specified as the size of one block.
 *
 * @see BLKSIZE
 */
typedef byte block[BLKSIZE];


/**
 * @typedef locations
 *
 * @brief A NULL terminated array of locations for blocks on disk.
 * Locations' indices are represented by 32-bit unsigned integers.
 */
typedef uint32_t* locations;

#endif /* GLOBDATA_H_ */
