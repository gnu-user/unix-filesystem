#include "index_block.h"
#include "glob_func.h"
#include "block_func.h"


data_index generate_index(uint32_t num_blocks)
{
	/* Current instance of data_index struct */
	data_index cur_data_index =
	{
		.index_location = 0,
		.data_locations = NULL
	};

	/* Array indexes and index_block length */
	uint32_t i = 0, j = 0;
	uint32_t index_len = floor(BLKSIZE / sizeof(uint32_t));
	locations tmp_data_locations = NULL;

	/* Index location, and index block */
	uint32_t index_location = 0;
	index index_block = NULL;
	//index index_block = calloc(index_len, sizeof(location));

	/* Get a free block location to write the index */
	index_location = get_free_block();

	/* Set the location of the first index block in data_index struct */
	cur_data_index.index_location = index_location;

	/* If the number of blocks is 0, write an empty index and return */
	if (num_blocks == 0)
	{
		index_block = (index) calloc(index_len, sizeof(uint32_t));
		write_block(index_location, (byte *)index_block);
		free(index_block);

		return cur_data_index;
	}

	while (num_blocks > 0)
	{
		tmp_data_locations = NULL;

		/* Allocate an index to write to disk */
		index_block = (index) calloc(index_len, sizeof(uint32_t));

		for (i = 0; i < (index_len - 1); ++i)
		{
			index_block[i] = get_free_block();

			/* Add the data location to data_index struct, free dynamic memory */
			tmp_data_locations = (locations) concat_len(cur_data_index.data_locations,
											&index_block[i], sizeof(uint32_t),
											sizeof(uint32_t));
			free(cur_data_index.data_locations);
			cur_data_index.data_locations = tmp_data_locations;

			--num_blocks;

			if (num_blocks == 0)
			{
				break;
			}
		}

		if (num_blocks > 0)
		{
			index_block[i] = get_free_block();
		}

		/* Write the index to the block specified */
		write_block(index_location, (byte *)index_block);

		/* Update the index location to the next index block location at the end of the current index
		 * and free the old index_block buffer in memory
		 */
		index_location = index_block[i];
		free(index_block);
	}

	return cur_data_index;
}


uint32_t rebuild_index(locations data_locations)
{
	/* Array indexes and index_block length */
	uint32_t i = 0, j = 0;
	uint32_t index_len = floor(BLKSIZE / sizeof(uint32_t));

	/* Index location, and index block */
	uint32_t index_location = 0;
	uint32_t first_index_location = 0;
	index index_block = NULL;

	/* Get a free block location to write the index */
	index_location = get_free_block();

	/* Set the location of the first index block */
	first_index_location = index_location;

	/* If data locations is NULL or the number of data locations is 0,
	 * write an empty index and return
	 */
	if (data_locations == NULL || data_locations[0] == NULL)
	{
		index_block = (index) calloc(index_len, sizeof(uint32_t));
		write_block(first_index_location, (byte *)index_block);
		free(index_block);

		return first_index_location;
	}

	while (data_locations[j] != NULL)
	{
		/* Allocate an index to write to disk */
		index_block = (index) calloc(index_len, sizeof(uint32_t));

		for (i = 0; i < (index_len - 1); ++i)
		{

			/* Check before we access the data_location array that it is not NULL
			 * before we write the data location to the index
			 */
			if (data_locations[j] != NULL)
			{
				index_block[i] = data_locations[j];
			}
			/* All of the data locations have been written to the index in memory */
			else
			{
				break;
			}

			/* Increment the index in the data locations array */
			++j;
		}

		/* If there are more data locations to write, link another index */
		if (data_locations[j] != NULL)
		{
			index_block[i] = get_free_block();
		}

		/* Write the index to the block specified */
		write_block(index_location, (byte *)index_block);

		/* Update the index location to the next index block location at the end of the current index
		 * and free the old index_block buffer in memory
		 */
		index_location = index_block[i];
		free(index_block);
	}

	/* Return the location of the first index block */
	return first_index_location;
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
	for (i = 0; i < (index_len - 1); ++i)
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
		tmp_data_blocks = (locations) concat_len(data_blocks, &index_block[i],
												sizeof(location), sizeof(location));

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
	if (index_block[i] != NULL)
	{
		data_blocks = iterate_index(index_block[i], data_blocks);
	}

	/* Index block doesn't link to another index, return the array of data locations */
	return data_blocks;
}


uint32_t calc_index_blocks(uint32_t num_blocks)
{
	return (uint32_t) ceil((double)(num_blocks) /
			(floor(BLKSIZE / (double)(sizeof(uint32_t))) - 1));
}


//TODO implement count files in dir
int count_files_in_dir(uint32_t location)
{
	locations loc = NULL;
	int i = 0;

	/**
	 * Need to make sure that if there are not locations in the index block that
	 * rather then null, 0 is returned.
	 */
	loc = iterate_index(location, NULL);
	if(loc == NULL)
	{
		return -1;
	}

	/**
	 * iterate through the loc pointer and determine the number of locations
	 */
	while(loc[i] != NULL)
	{
		i++;
	}

	return i;
}

/**
 * Need to be able to add a location onto the end of this list.
 */
int add_location (uint32_t index_block, uint32_t location)
{

}


locations index_block_locations(uint32_t location, locations index_blocks)
{
	/* Index length, which is the number of data locations stored in an index block */
	uint32_t index_len = floor(BLKSIZE / sizeof(location));
	/* Index_block read from disk */
	index index_block = calloc(index_len, sizeof(location));

	locations tmp_index_blocks = NULL;
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

	/* Read the index block successfully, concatenate the index block location
	 * to the array of index block locations */
	tmp_index_blocks = (locations) concat_len(index_blocks, &location,
											sizeof(location), sizeof(location));

	/* If tmp_index_blocks NULL an error occurred concatenating the data */
	if (tmp_index_blocks == NULL)
	{
		free(index_blocks);
		free(index_block);
		return NULL;
	}

	/* Free dynamic memory, assign index_blocks a pointer to the array of index block locations */
	free(index_blocks);
	index_blocks = tmp_index_blocks;

	/*
	 * Iterate through the index until we reach a NULL location
	 */
	for (i = 0; i < (index_len - 1); ++i)
	{
		/* No more locations stored in the index block, return the index block locations */
		if (index_block[i] == NULL)
		{
			/* Free dynamic memory and return the NULL terminated array of index blocks locations */
			tmp_index_blocks = (locations) concat(index_blocks, NULL, sizeof(location));
			free(index_blocks);
			free(index_block);
			return tmp_index_blocks;

		}
	}

	/* If the index block links to another index, iterate over the index block recursively */
	if (index_block[i] != NULL)
	{
		index_blocks = index_block_locations(index_block[i], index_blocks);
	}

	/* Index block doesn't link to another index, return the NULL terminated array of locations */
	return index_blocks;
}
