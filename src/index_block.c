#include "index_block.h"
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
data_index generate_index(uint32_t num_blocks)
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
	 *		write_block(where[j], what)
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
	 * 			write_block(where[j-1], &what)
	 * }
	 * 	//Return the location of the first index block.
	 * 	return where[0];
	 *
	 */
}

/*
int link_inode(uint32_t* index_block, uint32_t location)
{
	return 1;
} */


locations iterate_index(uint32_t location, locations data_blocks)
{
	/* Index_block read from disk */
	//uint32_t index_block[index_len] = { 0 };
	//index index_block = NULL;
	//index_block = (index) calloc(ceil(BLKSIZE / sizeof(location)), sizeof(location));
	/* Index length, which is the number of data locations stored in an index block */
	uint32_t index_len = floor(BLKSIZE / sizeof(location));
	index index_block = calloc(index_len, sizeof(location));

	locations tmp_data_blocks = NULL;
	uint32_t i = 0;

	/* Verify that the the index block location specified is valid */
	if (location <= 0 || location >= NUMBLKS)
	{
		/* Invalid index block location */
		free(index_block);
		return NULL;
	}

	/* Error reading the block */
	if (read_block(location, (byte *)index_block) < 0)
	{
		free(index_block);
		return NULL;
	}

	/*
	 * Add each data location in the index block to the array of data locations
	 * only iterate up to the 2nd last item as the index block may have a linked index
	 */
	for (i = 0; i < index_len - 1; ++i)
	{
		tmp_data_blocks = NULL;

		/* No more locations stored in the index block, return the locations */
		if (index_block[i] == NULL)
		{
			/* Free dynamic memory and return the NULL terminated array of data blocks locations */
			tmp_data_blocks = (locations) concat(data_blocks, NULL, sizeof(location));
			free(data_blocks);
			free(index_block);
			return tmp_data_blocks;

		}

		/* Concatenate the data block location to the array of data block locations */
		tmp_data_blocks = (locations) concat_len(data_blocks, &index_block[i], sizeof(location), 1);

		/* If tmp_data_blocks NULL an error occurred concatenating the data */
		if (tmp_data_blocks == NULL)
		{
			free(data_blocks);
			free(index_block);
			return NULL;
		}

		/* Free dynamic memory, assign data_blocks a pointer to the array of data block locations */
		free(data_blocks);
		data_blocks = tmp_data_blocks;
	}

	/* If the index block links to another index, iterate over the index block recursively */
	if (index_block[i+1] != NULL)
	{
		data_blocks = iterate_index(index_block[i+1], data_blocks);
	}

	// Index block doesn't link to another index, return the array of data locations
	return data_blocks;
}


uint32_t calc_index_blocks(uint32_t num_blocks)
{
	return 0;
}

int count_files_in_dir(uint32_t location)
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

locations index_block_locations(uint32_t location)
{

	return NULL;
}
