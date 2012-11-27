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


#include "initialize.h"
#include "block_func.h"
#include "super_block.h"
#include "free_block_list.h"
#include "index_block.h"
#include <math.h>
#include <stdbool.h>


uint32_t FBL_DATA_SIZE;
uint32_t FBL_TOTAL_SIZE;
uint32_t ROOT;


int sfs_initialize(int erase)
{
	FBL_DATA_SIZE = ceil((double) (NUMBLKS / BLKSIZE));
	FBL_TOTAL_SIZE = (uint32_t) ceil(
			FBL_DATA_SIZE / (floor(BLKSIZE / (double) (sizeof(uint32_t))) - 1))
			+ FBL_DATA_SIZE;
	ROOT = (uint32_t) (FBL_INDEX + FBL_TOTAL_SIZE);
	byte* buf = NULL;
	int root_dir = 0;
	int retval = 0;
	char root_name[] = "/";
	int variant = 0;
	char str[100];

	if (erase == 1 || erase == 0)
	{
		if (erase == 1)
		{
			/* Erase Disk and reallocate to free block list */
			retval = wipe_disk();

			if (retval != 0)
			{
				/*
				 * TODO validate this error code
				 */
				print_error(DISK_WRITE_ERROR);
				return retval;
			}
		}

		/*
		 * Initialize the Superblock struct with a pointer to the free block
		 * list block, a pointer to the root directory Inode block.
		 */
		superblock sb = { NUMBLKS * BLKSIZE, BLKSIZE, FBL_INDEX, ROOT, 0, NULL, 0 };

		uuid_generate(sb.uuid);

		/* Allocate a buffer to write to the block. */
		buf = allocate_buf(buf, BLKSIZE);

		/* Copy the superblock into to buffer */
		buf = (byte *) copy_to_buf((byte *) &sb, (byte *) buf, sizeof(sb), BLKSIZE);

		retval = write_block(SUPER_BLOCK, buf);
		free(buf);

		if (retval != 0)
		{
			/*
			 * Failed to write SB.
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_SB);
			return retval;
		}

		/* Initialize the free_block list starting at the next index after the
		 * super block
		 */
		retval = free_block_init();

		if (retval != 0)
		{
			/* Failed to write FBL.
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_FBL);
			return retval;
		}

		/*
		 * Delete the Root directory so it can be re-written
		 * TODO update this to use proper error handling
		 */
		buf = allocate_buf(buf, BLKSIZE);
		retval = write_block(ROOT, buf);

		/* Failed to delete root directory. */
		if (retval != 0)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(DISK_WRITE_ERROR);
			return retval;
		}

		/*
		 * Initialize the root directory. This will be the first block
		 * initialized outside of the super block. The root_dir will contain an
		 * Inode that points to a index block that is empty.
		 * TODO update this to use proper error handling
		 */
		retval = sfs_create(root_name, 1);

		if (retval <= 0)
		{
			/*
			 * Failed to write root directory.
			 * TODO validate this error code
			 */
			print_error(DISK_WRITE_ERROR);
			return retval;
		}

		/*
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}
	else
	{
		/*
		 * TODO validate this error code
		 */
		print_error(INVALID_PARAMETER);
		return -1;
	}
}


int free_block_init(void)
{
	data_index idx = { 0 };
	free_block_list* fbl = NULL;
	block* data_blocks = NULL;
	uint32_t i = 0;

	/* Wipe the entire FBL in memory, everything is marked as free */
	if (wipe_fbl() == NULL)
	{
		/* Error occurred updating the FBL in memory
		 * TODO validate this error code
		 */
		print_error(ERROR_UPDATING_FBL);
		return -1;
	}

	/* Initialize the new FBL in memory, mark the superblock as used */
	fbl = update_fbl(NULL, NULL);
	if (fbl == NULL )
	{
		/* Error occurred updating the FBL in memory
		 * TODO validate this error code
		 */
		print_error(ERROR_UPDATING_FBL);
		return -1;
	}

	/* Write the new FBL to disk */
	idx = generate_index(FBL_DATA_SIZE);

	if (idx.index_location == NULL)
	{
		/* Error occurred generating the FBL index.
		 * TODO validate this error code
		 */
		print_error(INDEX_ALLOCATION_ERROR);
		return -1;
	}

	/* Segment the data blocks and write them at the locations set aside by the index */
	data_blocks = segment_data_len(fbl, NUMBLKS);
	if (data_blocks == NULL)
	{
		/* Error occurred segmenting the output data.
		 * TODO validate this error code
		 */
		free(data_blocks);
		print_error(ERROR_BUFFER_SEGMENTATION);
		return -1;
	}

	while (idx.data_locations[i] != NULL)
	{
		if (write_block(idx.data_locations[i], data_blocks[i]) != 0)
		{
			/* Error occurred writing block to disk.
			 * TODO validate this error code
			 */
			print_error(DISK_WRITE_ERROR);
			return -1;
		}
		i++;
	}

	/* TODO validate this error code */
	free(data_blocks);
	print_error(SUCCESS);
	return 0;
}


int wipe_disk(void)
{
	/* Create the null block of data */
	byte* buffer = NULL;

	buffer = allocate_buf(buffer, BLKSIZE);

	int retval = 0;

	/* Go block to block setting them to null */
	for (uint32_t i = 0; i < NUMBLKS; i++)
	{
		retval = write_block(i, buffer);
		if (retval != 0)
		{
			/*
			 * Error occurred writing block to disk.
			 * TODO validate this error code
			 */
			print_error(DISK_WRITE_ERROR);
			return retval;
		}
	}
	free(buffer);

	/* TODO validate this error code */
	print_error(SUCCESS);
	return 0;
}
