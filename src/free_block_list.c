#include "free_block_list.h"
#include <stdbool.h>


static free_block_list fbl =
{
	.free_blocks = { false }
};


// TODO THIS NEEDS TO BE CALLED
free_block_list* get_free_block_list(void)
{
	uint32_t i = 0;
	/* Temporary fbl buffer, bool* is used instead of free_block_list* as the
	 * blocks read from disk may be > than length of free_block_list struct
	 */
	bool* tmp_fbl = NULL;
	uint32_t offset = 0;
	uint32_t fbl_location = 0;
	locations fbl_data_locations = NULL;
	/* Buffers containing a single fbl data block read from disk */
	bool fbl_buf[BLKSIZE] = { false };
	bool empty_block[BLKSIZE] = { false };

	/* If the current free block list in memory has not been set (the
	 * superblock at index 0 is marked as free) read the FBL from disk
	 */
	if (fbl.free_blocks[0] == false)
	{
		/* Get the FBL index location from the superblock */
		fbl_location = get_free_block_index();

		/* Get the FBL data locations */
		fbl_data_locations = iterate_index(fbl_location, NULL);

		/* Check if an error occurred getting the FBL data locations */
		if (fbl_data_locations == NULL)
		{
			free(fbl_data_locations);
			return NULL;
		}

		/* Read the fbl from disk into memory */
		while (fbl_data_locations[i] != NULL)
		{
			/* Check if an error occurred reading the block */
			if (read_block(fbl_data_locations[i], (byte *)fbl_buf) < 0)
			{
				free(fbl_data_locations);
				return NULL;
			}

			/* Increase the size of the tmp free block list array for one more block */
			tmp_fbl = (bool*) realloc(tmp_fbl, (i + 1) * BLKSIZE);

			/* Initialize the data in the tmp fbl to false before copying in the fbl buf */
			memcpy(tmp_fbl + offset, empty_block, BLKSIZE);

			/* Copy the fbl buf at the next offset in the tmp free block list */
			memcpy(tmp_fbl + offset, fbl_buf, BLKSIZE);

			offset += BLKSIZE;
		}

		/* Update the static instance of fbl in memory with the fbl read from disk */
		if (tmp_fbl != NULL)
		{
			/* Overwrite the current fbl with the fbl from disk */
			memcpy(&fbl, tmp_fbl, sizeof(free_block_list));

			/* Free the buffers */
			free(fbl_data_locations);
			free(tmp_fbl);
		}
		else
		{
			free(fbl_data_locations);
			return NULL;
		}
	}

	return &fbl;
}


locations calc_total_free_blocks(void)
{
	//1. Get the free block list.
	//2. Traverse it and add any blocks marked as empty to an array of type free_indices.
	//3. Return the array.

/*
	locations_buf = calloc(NUMBLKS, sizeof(free_location))
	count = 0

	for (i = 0, i < NUMBLKS, i++)
	{
		if (! fbl[i])
		{
			locations_buf[count] = i
			count++
		}
	}

	return locations_buf

 */
	locations free_blocks = NULL;
	uint32_t blocks_found = 0;

	/* Get the location of the next available free block */
	for (uint32_t i = 0; i < NUMBLKS; ++i)
	{
		if (fbl.free_blocks[i] == false)
		{
			/* Reallocate more memory to store the next location */
			free_blocks = (locations) realloc(free_blocks, ((blocks_found + 1) * sizeof(uint32_t)));

			/* Add the free location to the array of free blocks */
			free_blocks[blocks_found] = i;

			++blocks_found;
		}
	}

	/* If free_blocks is NULL there are no free blocks available */
	if (free_blocks == NULL)
	{
		return 0;
	}

	/* Null terminate the array of free blocks locations and return it */
	free_blocks = (locations) realloc(free_blocks, ((blocks_found + 1) * sizeof(uint32_t)));
	free_blocks[blocks_found] = NULL;

	return free_blocks;
}


locations calc_num_free_blocks(uint32_t num_blocks)
{
	//1. Get the free block list.
	//2. Traverse it and add num_blocks specified marked as empty to an array of type free_indices.
	//3. Return the array.

	/*
	    // num_blocks + 1 items in order to null terminate
		locations_buf = calloc(num_blocks +1, sizeof(free_location))
		count = 0

		for (i = 0, i < NUMBLKS, i++)
		{
			// If found the num_blocks specified break
			if (count == num_blocks)
			{
				break;
			}
			if (! fbl[i])
			{
				locations_buf[count] = i
				count++
			}
		}

		return locations_buf

	 */

	locations free_blocks = NULL;
	uint32_t blocks_found = 0;

	/* Get the location of the next available free block */
	for (uint32_t i = 0; i < NUMBLKS && blocks_found < num_blocks; ++i)
	{
		if (fbl.free_blocks[i] == false)
		{
			/* Reallocate more memory to store the next location */
			free_blocks = (locations) realloc(free_blocks, ((blocks_found + 1) * sizeof(uint32_t)));

			/* Add the free location to the array of free blocks */
			free_blocks[blocks_found] = i;

			++blocks_found;
		}
	}

	/* If free_blocks is NULL there are no free blocks available */
	if (free_blocks == NULL)
	{
		return 0;
	}

	/* If the number of free blocks found is less than the number of free blocks
	 * requested then there are not enough free blocks available
	 */
	if (blocks_found < num_blocks)
	{
		return 0;
	}

	/* Null terminate the array of free blocks locations and return it */
	free_blocks = (locations) realloc(free_blocks, ((blocks_found + 1) * sizeof(uint32_t)));
	free_blocks[blocks_found] = NULL;

	return free_blocks;
}


uint32_t get_free_block(void)
{
	/* Get the location of the next available free block */
	locations free_block = calc_num_free_blocks(1);
	uint32_t free_block_loc = 0;

	/* If the free_block is NULL there are no more free blocks available */
	if (free_block == NULL)
	{
		return 0;
	}

	/* Mark the free_block location as used in the free block list and return the location */
	if (update_fbl(free_block, NULL ) != NULL)
	{
		/* Copy the single free block location and free the dynamic memory */
		free_block_loc = free_block[0];
		free(free_block);

		return free_block_loc;
	}

	/* Otherwise, an error occurred updating the free block list */
	return 0;
}


free_block_list* update_fbl(locations used,
							locations free)
{
	/* Always ensure that the  first fbl location is marked as used by the superblock */
	fbl.free_blocks[0] = true;
	uint32_t i = 0;

 	/* Iterate through each item in the used and free locations array,
 	 * for each item in the array update the free block list
	 */
	if (used != NULL)
	{
		while (used[i] != NULL)
		{
			printf("used location %d\n", used[i]);
			/* Mark each of the fbl locations specifed as used */
			fbl.free_blocks[used[i]] = true;
			++i;
		}
	}
	if (free != NULL)
	{
		i = 0;

		while (free[i] != NULL)
		{
			/* Mark each of the fbl locations specifed as free */
			fbl.free_blocks[free[i]] = false;
			++i;
		}
	}

	return &fbl;
}


int sync_fbl(void)
{
	/*
		 * Writes the FBL to the index locations pointed to by the
		 *
		 * fbl_location = get_free_block_index();
		 *
		 * fbl_data_locations = iterate_index(fbl_location, NULL);
		 *
		 * fbl_data_blocks = segment_data_len(fbl, NUMBLKS);
		 *
		// Check that the data_blocks were segmented properly
		//	if (data_blocks == NULL)
		//	{
		//		// Error occurred segmenting the data blocks
		//		return -1;
		//	}
		//
		//	while (idx.data_locations[i] != NULL)
		//	{
		//		write_block(idx.data_locations[i], data_blocks[i]);
		//		i++;
		//	}
		*/
	return 0;
}
