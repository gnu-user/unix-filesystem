#include "index_block.h"
#include "glob_data.h"
#include "glob_func.h"
#include "block_func.h"


/*
 * TODO for get_free_block need to handle updating the fbl after calling get_free_block
 * otherwise get_free_block will keep returning the same free block location...
 *
 * TODO Need to handle what to return from generate_index
 *
 * Every call to generate_index should be followed by two commands:
 * 1) Journal: Link the newly created FBL.
 * 2) Journal: Link the newly created index block to it's inode.
 */
uint32_t generate_index(uint32_t num_blocks)
{
	/*
	 * PSEUDOCODE:
	 *
	 * i, j = 0
	 * index_block length is BLKLENGTH / sizeof(uint32_t)
	 *
	 * where[j] = get_free_block(fbl, 1)
	 *
	 * // If the data length is 0, write an empty index
	 * if data length == 0
	 * {
	 *		calloc(what, index length)
	 *		write(where[j], what)
	 * }
	 *
	 * while (data length > 0)
	 * {
	 * 		// calloc an index to write to the block
	 * 		calloc(what, index length)
	 * 		for (i = 0, i < index_block length, i++)
	 * 		{
	 * 			what[i] = get_free_block(fbl, 1)
	 * 			data length --
	 *
	 * 			if data length == 0
	 * 			{
	 * 				break;
	 * 				}
	 * 			}
	 *
	 * 			j++
	 *
	 * 			if data length != 0
	 * 			{
	 * 				where[j] = get_free_block(fbl, 1)
	 * 				what[i + 1] = where[j]
	 * 			}
	 *
	 *
	 * 			// Write the index to the block specified
	 * 			write(where[j-1], &what)
	 * }
	 * 	//Return the location of the first index block.
	 * 	return where[0];
	 *
	 */
}

int link_inode(uint32_t* index_block, uint32_t location)
{
	return 1;
}

// TODO FIX THE VARIABLE NAMES THIS CAN ALSO BE USED TO RETURN THE
// LOCATIONS OF INDODES IN THE CASE OF A DIRECTORY
locations iterate_index(uint32_t location, locations data_blocks)
{
/*
	// Read the index block from the drive at location specified
	index block = read_block(location)
	uint32_t i  = 0;

	/*
	 * Add each data location in the index block to the array of data locations
	 * only iterate up to the 2nd last item as the index block may have a linked index
	 *
	for (i = 0; i < ceil(BLKSIZE / sizeof(location)) - 1; i++)
	{
		if block[i] == NULL
		{
			return concat(data_blocks, NULL)
		}

		concat(data_blocks, block[i])
	}


	// If the index block links to another index, iterate over the index block recursively
	if (block[i+1] != null)
	{
		iterate_indix(block[i+1], data_blocks);
	}

	// Index block doesn't link to another index, null terminate the array of data locations
	return concat(data_blocks, NULL);
*/
}

int count_locations(uint32_t location)
{
	locations loc = NULL;

	/**
	 * Need to make sure that if there are not locations in the index block that
	 * rather then null, 0 is returned.
	 */
	if(iterate_index(location, loc) == NULL)
	{
		return -1;
	}

	/**
	 * iterate through the loc pointer and determine the number of locations
	 */
	return 0;
}

uint32_t* index_block_locations(uint32_t location)
{

	return NULL;
}
