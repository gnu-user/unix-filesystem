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
#include "error.h"

#ifndef INDEX_BLOCK_H_
#define INDEX_BLOCK_H_


/**
 * @typedef index
 *
 * @brief This type definition uses an array of 32-bit unsigned
 * integers to represent index locations on disk.
 *
 * @details This type definition represents an index block data
 * structure. It is supported by pseudo-object oriented methods
 * in order to return arrays of variables to functions by way of
 * pointer arithmetic based logical segmentations of data types
 * in memory.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
typedef uint32_t* index;


/** 
 * @struct data_index
 *
 * @brief A data structure containing the location of the first index
 * of an index data structure and an array of the data locations.
 *
 * @details This data structure allows for a pseudo-object
 * oriented approach to returning an 'object' which consists of an
 * unsigned 32-bit integer and an array. This data structure supports
 * the index block data structure and is used to pass complex encapsulated
 * data types between functions.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
typedef struct {
	uint32_t index_location;
	locations data_locations;
} data_index;


/**
 * @brief Generates the indexes for the data blocks and then writes the indexes
 * (which contain the locations of data blocks) to disk.
 *
 * @details This function returns a data_index pseudo-object which
 * contains the location of the first index block, and the locations
 * of all the data blocks indexed by the all the indices (spanning the
 * entire index data structure).
 *
 * @param num_blocks The number of blocks to generate indexes for.
 *
 * @return Returns a data_index struct which contains the location of the first
 * index block, and the locations of all data blocks indexed
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
data_index generate_index(uint32_t num_blocks);


/**
 * @brief Takes a series of loose data block locations and builds a new
 * index to link them with an inode.
 *
 * @details This function takes a NULL terminated array of data locations
 * and turns it into a new index structure, then writes it on disk and
 * returns the location of the first index block.
 * The function operates similar to generate_index except you already
 * have all the data locations. If an error occurs 0 is returned.
 * If NO data_locations are specified an empty index is created and the location
 * is returned.
 *
 * @param data_locations A NULL terminated array of data locations, if NO data
 * locations are provided an empty index is created and the location is returned
 *
 * @return The location of the FIRST index block, if an error occurs 0 is returned
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
uint32_t rebuild_index(locations data_locations);


/**
 * @brief This function takes an index block data structure and returns
 * the locations of all data blocks which it links to.
 *
 * @details This function iterates recursively through the index blocks
 * and returns a pointer to a NULL terminated array containing all of
 * the data block locations stored in the indices. In the case of large
 * files that require multiple indexes, when we reach the value
 * ceil(BLOCKSIZE/sizeof(uint32_t)
 * which is the last entry in the index block, we recursively call
 * iterate_index on the index block at this index.
 * When we reach a NULL location inside the index block, we have
 * reached the end of the indexes. The function returns a NULL pointer
 * if an error occurred.
 *
 * @param location The location of the first index block to iterate through.
 *
 * @param data_blocks An argument used by the function when it recursively
 * calls itself, the argument should be NULL when calling iterate_index
 * for the first index location.
 *
 * @return Returns a pointer to a NULL terminated array containing
 * all of the data block locations stored in the indices,
 * the pointer is NULL if an error occurred.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
locations iterate_index(uint32_t location, locations data_blocks);


/**
 * @brief Calculates the number of index blocks that are needed in order to write
 * the number of data blocks specified to the file system.
 *
 * @details This function uses a calculation based on the specified block size
 * of the disk in order to determine how many locations can be indexed within
 * one block, and then divides the number of specified blocks by this value.
 * Since fractions of blocks are not allowed, the function then ceilings the
 * resultant value in order to provide the full length of the required data
 * structure.
 *
 * @param num_blocks The number of data blocks required to be indexed.
 *
 * @return Returns the number of index blocks needed to write the data blocks to the
 * file system.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
uint32_t calc_index_blocks(uint32_t num_blocks);


/**
 * @brief Wrapper for iterate_index which simply gives you a count
 * of the number of files in a directory.
 *
 * @param location The location of the index block on disk to iterate across.
 *
 * @return Returns the number of locations found in the index block.
 * If return = 0 then the directory is empty. If return > 0 then the
 * function was successful, and if return = -1 then the
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
int count_files_in_dir(uint32_t location);


/**
 * @brief Provides the locations of the index blocks within an
 * index block data structure.
 *
 * @details This function iterates recursively through the index blocks in
 * an index block data structure and returns a pointer to a NULL terminated
 * array containing all of the index block locations on disk. If an error
 * occurs then NULL is returned.
 *
 * @param location The location of the first index block.
 *
 * @param index_blocks An argument used by the function when it recursively calls itself,
 * the argument should be NULL when calling index_block_locations for the first index location.
 *
 * @return Returns a list of index block locations. If there is an error the value returned
 * will be NULL.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
locations index_block_locations(uint32_t location, locations index_blocks);


#endif /* INDEX_BLOCK_H_ */
