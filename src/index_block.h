#include "glob_data.h"

#ifndef INDEX_BLOCK_H_
#define INDEX_BLOCK_H_

//TODO use malloc for this; it should be size: ceil(BLOCKSIZE/sizeof(uint32_t))
typedef uint32_t* index;

// Array of locations for blocks on disk
typedef uint32_t* locations;

// A single location for a block on disk
//typedef uint32_t location;

//TODO add a linked list for storing the indices



/**
 * Generates the indexes for the data blocks and writes the indexes containing
 * the locations to disk.
 *
 * It returns the location of the first index, which can then be used to write the
 * data to the blocks.
 *
 * TODO document this more
 *
 * @param num_blocks The number of blocks to generate indexes for
 *
 *
 */
uint32_t generate_index(uint32_t num_blocks);




index read_index(uint32_t index_on_disk);

/*
 * Adds a location to the next available entry in the index block, if the index block is
 * full then calls a helper function, link_index_block(), which creates another block and links
 * it to the end of the index_block.
 *
 * TODO remove
 */
//add_location(uint32_t* index_block, uint32_t location);



/**
 * This should take the location of the location to be removed.
 *
 * @param the list of locations TODO see if this is really needed
 * @param the location to be removed
 *
 * @return if > 0 success
 * if <= 0 failure
 */
int remove_location(uint32_t* index_block, uint32_t location);



void link_index();

/**
 * link inode links the inode to the index block of the parent (directory)
 *
 * @param the index block list
 * @param the location to be added to the index block
 *
 * @return an integer value
 * if value > 0 then function was successful
 * otherwise the function has failed
 *
 * TODO verify if this is the right function for the job.
 */
int link_inode(uint32_t* index_block, uint32_t location);

// TODO FIX THE VARIABLE NAMES THIS CAN ALSO BE USED TO RETURN THE
// LOCATIONS OF INDODES IN THE CASE OF A DIRECTORY
// TODO FIX THIS FUNCTION DESCRIPTION, ITS OUT OF DATE WITH THE CURRENT CODE
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
locations iterate_index(uint32_t location, locations data_blocks);

/**
 * Count the number of locations given the index block's location
 *
 * @param location the location of the index block on disk
 *
 * @return the number of locations found in the index block
 * if number = 0 then the directory is empty
 * if number > 0 then the function was successful
 * if number < 0 then the function was unsuccessful
 */
int count_locations(uint32_t location);

/**
 * Locate the index block locations on disk.
 *
 * @param location the location of the initial index block
 *
 * @return a list of index blocks locations
 * if there is an error the value returned will be NULL
 */
uint32_t* index_block_locations(uint32_t location);

#endif /* INDEX_BLOCK_H_ */
