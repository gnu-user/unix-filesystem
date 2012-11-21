#include "glob_data.h"

#ifndef INDEX_BLOCK_H_
#define INDEX_BLOCK_H_

// TODO use malloc for this; it should be size: ceil(BLOCKSIZE/sizeof(uint32_t))
typedef uint32_t* index;

// Array of locations for blocks on disk
typedef uint32_t* locations;

/* Stuct containing the location of the first index and an array of the
 * data location
 */
typedef struct {
	uint32_t index_location;
	locations data_locations;
} data_index;

// A single location for a block on disk
//typedef uint32_t location;

// TODO add a linked list for storing the indices


/**
 *
 * TODO NEED TO UPDATE THE GENERATE_INDEX PSEUDOCODE TO HANDLE RETURNING
 * THE DATA_INDEX STRUCT
 *
 * Generates the indexes for the data blocks and then writes the indexes
 * (which contain the locations of data blocks) to disk.
 *
 * It returns a data_index struct which contains the location of the first index block,
 * and the locations of all the data blocks indexed by the all the indices (spanning the
 * entire index data structure).
 *
 *
 * @param num_blocks The number of blocks to generate indexes for
 * @return Returns a data_index struct which contains the location of the first
 * index block, and the locations of all data blocks indexed
 *
 */
data_index generate_index(uint32_t num_blocks);

/**
 * Wrapper for block_read() which returns the block
 *TODO remove unless we really need this for something we haven't thought of yet (JUST FUCKIN' REMOVE IT)
 */
//index read_index(uint32_t index_location);

/*
 * Adds a location to the next available entry in the index block, if the index block is
 * full then calls a helper function, link_index_block(), which creates another block and links
 * it to the end of the index_block.
 *
 * TODO remove this too, you fuckin' retard
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
 * TODO REMOVE THIS BULLSHIT YOU STUPID IDIOT, WE REBUILD THE INDEX EVERY TIME WE MODIFY A FILE
 */
//int remove_location(uint32_t* index_block, uint32_t location);


/**
 * TODO REMOVE THIS, THIS IS SUPPOSED TO BE A JOURNALLED OPERATION! WHAT THE FUCK!??!
 */
//void link_index();

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
 * TODO REMOVE THIS, IT ALREADY EXISTS IN THE JOURNAL (THIS IS A JOURNALLED OPERATION REGARDLESS YOU TARD)
 */
//int link_inode(uint32_t* index_block, uint32_t location);


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
 * Wrapper for iterate_index which simply gives you a count of the number of files in a directory.
 *
 * @param location The location of the index block on disk to iterate across.
 *
 * @return the number of locations found in the index block
 * if return = 0 then the directory is empty
 * if return > 0 then the function was successful
 * if return = -1 then the function was unsuccessful
 */
int count_locations(uint32_t location);

/**
 * Locate the index block locations on disk. Used for deleting the index blocks once
 * the index datastructure has been traversed and all the data blocks have been freed.
 *
 * @param location The location of the first index block.
 *
 * @return Returns a list of index block locations.
 * If there is an error the value returned will be NULL.
 */
locations index_block_locations(uint32_t location);

#endif /* INDEX_BLOCK_H_ */
