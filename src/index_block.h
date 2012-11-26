#include "glob_data.h"
#include "error.h"

#ifndef INDEX_BLOCK_H_
#define INDEX_BLOCK_H_


typedef uint32_t* index;

/* Stuct containing the location of the first index and an array of the
 * data locations
 */
typedef struct {
	uint32_t index_location;
	locations data_locations;
} data_index;


/**
 *
 * TODO NEED TO UPD	ATE THE GENERATE_INDEX PSEUDOCODE TO HANDLE RETURNING
 * THE DATA_INDEX STRUCT
 *
 * Generates the indexes for the data blocks and then writes the indexes
 * (which contain the locations of data blocks) to disk.
 *
 * It returns a data_index struct which contains the location of the first index block,
 * and the locations of all the data blocks indexed by the all the indices (spanning the
 * entire index data structure).
 *
 * @param num_blocks The number of blocks to generate indexes for
 * @return Returns a data_index struct which contains the location of the first
 * index block, and the locations of all data blocks indexed
 *
 */
data_index generate_index(uint32_t num_blocks);


/**
 * Takes a NULL terminated array of data locations and turns it into a new
 * index structure, then writes it on disk and returns the location of
 * the first index block. The function operates similar to generate_index
 * except you already have all the data locations. If an error occurs 0 is
 * returned.
 *
 * If NO data_locations are specified an empty index is created and the location
 * is returned.
 *
 * @param data_locations A NULL terminated array of data locations, if NO data
 * locations are provided an empty index is created and the location is returned
 *
 * @return The location of the FIRST index block, if an error occurs 0 is returned
 *
 * 1. For each data locations
 * 2. get another block and link it inside the first block
 * 3. write the first block
 * 4. write the second block
 * 5. repeat until you hit null in the buffer
 */
uint32_t rebuild_index(locations data_locations);


/**
 * Iterates recursively through the index blocks and returns a pointer to a NULL terminated
 * array containing all of the data block locations stored in the indices. In the case of
 * large files that require multiple indexes, when we reach the value
 * ceil(BLOCKSIZE/sizeof(uint32_t), which is the last entry in the index block, recursively
 * call iterate_index on the index block at this index. When we reach a NULL location inside
 * the index block, we have reached the end of the indexes.
 *
 * The function returns a NULL pointer if an error occurred
 *
 * @param location The location of the first index block to iterate through
 * @param data_blocks An argument used by the function when it recursively calls itself,
 * the argument should be NULL when calling iterate_index for the first index location.
 *
 * @return A pointer to a NULL terminated array containing all of the data block locations
 * stored in the indices, the pointer is NULL if an error occurred
 */
locations iterate_index(uint32_t location, locations data_blocks);


/**
 * Calculates the number of index blocks that are needed in order to write
 * the number of data blocks specified to the filesystem
 *
 * @param num_blocks The number of data blocks
 *
 * @return The number of index blocks needed to write the data blocks to the
 * file system
 */
uint32_t calc_index_blocks(uint32_t num_blocks);


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
int count_files_in_dir(uint32_t location);


/**
 * Iterates recursively through the index blocks and returns a pointer to a NULL terminated
 * array containing all of the index block locations on disk. If an error occurs then NULL
 * is returned.
 *
 * @param location The location of the first index block.
 * @param index_blocks An argument used by the function when it recursively calls itself,
 * the argument should be NULL when calling index_block_locations for the first index location.
 *
 * @return Returns a list of index block locations. If there is an error the value returned
 * will be NULL.
 */
locations index_block_locations(uint32_t location, locations index_blocks);


#endif /* INDEX_BLOCK_H_ */
