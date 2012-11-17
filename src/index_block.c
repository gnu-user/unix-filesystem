#include "index_block.h"
#include "globdata.h"


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
location generate_index(byte* data)
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
