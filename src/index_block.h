/*
 * index_block.h
 *
 *  Created on: Nov 16, 2012
 *      Author: jon
 */
#include <stdint.h>
#include "globdata.h"

//TODO use malloc for this; it should be size: ceil(BLOCKSIZE/sizeof(uint32_t))
typedef uint32_t* index_block;

// Array of locations for the index blocks on disk
typedef uint32_t* locations;

// A single location
typedef uint32_t location;

//TODO add a linked list for storing the indices



/**
 * Generates the indexes for the data blocks and writes the indexes containing
 * the locations to disk.
 *
 * It returns the location of the first index, which can then be used to write the
 * data to the blocks.
 */
location generate_index(byte* data);




index_block read_index_block(uint32_t index_on_disk);

/*
 * Adds a location to the next available entry in the index block, if the index block is
 * full then calls a helper function, link_index_block(), which creates another block and links
 * it to the end of the index_block.
 */
add_location(uint32_t* index_block, uint32_t location);




remove_location();

void link_index_block();

/**
 * Get the first index block, and increase the length of the buffer by one for each index we get.
 * When we reach the value ceil(BLOCKSIZE/sizeof(uint32_t) = the last entry in the index block, recursively
 * call iterate_index on the index block at this index.
 * When we reach NULL inside the index block, we have reached the end of the indexes.
 * Add this NULL value as the last entry in the array of indices returned.
 *
 * @param cur_index The current index block called at each recursive iteration
 * @param array_indices Array of the indices for the index blocks on disk, updated
 * with each successive recursive call
 *
 * @return The pointer to the array_indices containing an array of the indices for the
 * index blocks on disk, NULL if error occurred.
 *
 */
uint32_t* iterate_index_blocks(index_block *cur_index, locations *cur_locations);
