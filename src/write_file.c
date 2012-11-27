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


#include "glob_data.h"
#include "block_func.h"
#include "I_node.h"
#include "system_open_file_table.h"
#include "index_block.h"
#include "write_file.h"
#include <math.h>


block* modify_data(int32_t start, uint32_t length, byte* data_buf, byte* actual_data)
{
	uint32_t j = 0;
	block* data_blocks = NULL;
	byte* tmp_data_buf = NULL;
	uint32_t i = 0;

	/* If the starting point is provided alter the data buffer starting at that point */
	if (start >= 0)
	{
		for(uint32_t i = start; i < (start + length); ++i, ++j)
		{
			/* Error if the length is longer than the data buffer or
			 * actual data , buffer overrun */
			if (data_buf[i] == NULL || actual_data[j] == NULL)
			{
				return NULL;
			}

			/* Copy the actual data into the data buffer at the offset, i */
			memcpy(&data_buf[i], &actual_data[j], sizeof(byte));
		}

		/* Segment the data into blocks */
		data_blocks = segment_data(data_buf);
	}
	/* If the starting point is -1 append the actual data to the data buffer */
	else if (start == -1)
	{
		/* Append the actual data to the data buffer */
		tmp_data_buf = (byte*) concat_len(data_buf, actual_data, sizeof(byte), length);

		/* Segment the data into blocks and free the temporary buffer */
		data_blocks = segment_data(tmp_data_buf);
		free(tmp_data_buf);
	}

	return data_blocks;
}


block* segment_data(byte* data_buf)
{
	uint32_t i = 0;
	uint32_t length = 0;
	uint32_t blocks = 0;
	byte empty_block[BLKSIZE] = { NULL };

	/* The offset in the data buffer to copy the data into the block */
	uint32_t offset = 0;
	block* data_blocks = NULL;

	/* Get the length of the data buffer in bytes and the number of blocks
	 * to place the data into
	 */
	while (data_buf[i] != NULL)
	{
		++i;
	}

	/* Update the length and number of blocks */
	length = i;
	blocks = (uint32_t) ceil((double)length / BLKSIZE);


	/* Copy each block into a 2D array containing the blocks */
	for (i = 0; i < blocks; ++i)
	{
		/* Increase the size of the data blocks array for one more block */
		data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(block));

		/* Initialize the data in the block to NULL before copying in the data buf */
		memcpy(&data_blocks[i], empty_block, BLKSIZE);

		/* Copy the data_buf at the next offset into the array of data blocks */
		if (length >= BLKSIZE)
		{
			memcpy(&data_blocks[i], (data_buf + offset), BLKSIZE);
		}
		else
		{
			memcpy(&data_blocks[i], (data_buf + offset), length);
		}

		length -= BLKSIZE;
		offset += BLKSIZE;
	}

	/* Increase the data_blocks array for a final NULL termination block */
	data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(block));
	memcpy(&data_blocks[i], empty_block, BLKSIZE);

	return data_blocks;
}


block* segment_data_len(byte* data_buf, uint32_t length)
{
	uint32_t i = 0;
	uint32_t blocks = (uint32_t) ceil((double)length / BLKSIZE);
	byte empty_block[BLKSIZE] = { NULL };

	/* The offset in the data buffer to copy the data into the block */
	uint32_t offset = 0;
	block* data_blocks = NULL;

	/* Copy each block into a 2D array containin the blocks */
	for (i = 0; i < blocks; ++i)
	{
		/* Increase the size of the data blocks array for one more block */
		data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(block));

		/* Initialize the data in the block to NULL before copying in the data buf */
		memcpy(&data_blocks[i], empty_block, BLKSIZE);

		/* Copy the data_buf at the next offset into the array of data blocks */
		memcpy(&data_blocks[i], (data_buf + offset), BLKSIZE);
		offset += BLKSIZE;
	}

	/* Increase the data_blocks array for a final NULL termination block */
	data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(block));
	memcpy(&data_blocks[i], empty_block, BLKSIZE);

	return data_blocks;
}


/*
 * High level pseudocode for sfs_write, refer to the function prototype
 * in write_file.h for information about calling/using the function.
 *
 * blocks_needed = 1 //FOR INODE
 * data_blocks = iterate_index(inode.location)
 * data_buf = read_in_data(data_blocks)
 *
 * if start > 0
 * 	if start + length > length of data_blocks in bytes
 * 		return invalid write past file size
 * 	data_buf = data_buf{until_start} conact mem_pointer conact data_buf
 * 	after start + length}
 * if start == -1
 * 	data_buf = data_buf{all} concat mem_pointer
 *
 * divide into blocks(data_buf)
 * data += get number of data blocks
 * if(calc_num_free_blocks(data + num_of_index_blocks(data-1))) == NULL) //1 for the inode
 * 	return 0;
 * inode_location = get_free_block();
 * data_blocks data_location = generate_index(d)
 *
 * int i = 0;
 * while(data_location[i] != NULL)
 * 	write_block(data_location.data_blocks[i], databuf[i])
 * 	i++;
 * populate_inode (data_location.index_block)
 * link parent's index block to inode
 */
int sfs_write(int fd, int start, int length, byte *mem_pointer)
{
	//TODO create encryption
	//TODO create decryption
	uint32_t blocks_needed = 0;
	byte* buf = NULL;
	inode inode_write = get_null_inode();
	locations new_inode_loc = NULL;
	locations data_block_locations = NULL;
	byte* temp = NULL;
	byte* data_buf = NULL;
	locations data_location = NULL;
	uint32_t inode_loc = NULL;
	uint32_t first_index = NULL;
	block* data_block = NULL;
	locations old_index_block = NULL;
	time_t cur_date;
	int retval = 0;
	int i = 0;
	locations fbl = NULL;
	uint32_t k = 0;

	/* TODO split this into two different error codes/returns */
	if(fd >= 0 && fd < NUMOFL && length > 0 && start >= -1)
	{
		/*
		 * Validate the file descriptor on the system-wide-open file table
		 *  - If the file descriptor is not found return error
		 */
		if (validate_fd(fd) < 0)
		{
			/*
			 * Invalid file descriptor.
			 * TODO validate this error code
			 */
			print_error(INVALID_FILE_DESCRIPTOR);
			return 0;
		}

		blocks_needed++; /* Inode block space */
		inode_write = get_swoft_inode(fd);
		inode_loc = get_inode_loc(fd);
		data_block_locations = iterate_index(inode_write.location, NULL);

		old_index_block = index_block_locations(inode_write.location, NULL);

		if(old_index_block == NULL)
		{
			/*
			 * TODO get error code
			 * Error old index blocks not found
			 */
			return -1;
		}

		if(data_block_locations == NULL)
		{
			/*
			 * Invalid Index Block
			 * TODO validate this error code
			 */
			print_error(INDEX_ALLOCATION_ERROR);
			return -1;
		}

		if(data_block_locations[0] != NULL)
		{
			data_buf = get_data(data_block_locations);
			blocks_needed += calc_num_blocks(data_buf);
		}

		if(start >= 0)
		{
			if(data_block_locations[0] == NULL)
			{
				/*
				 * Invalid override
				 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
				 */
				return -1;
			}
			if((start + length) > calc_num_bytes(data_buf))
			{
				/*
				 * Write past EOF
				 * TODO validate this error code
				 */
				print_error(FILE_PAST_EOF);
				return -1;
			}
			/*
			 * No new data blocks will be needed
			 */
		}
		else if(start == -1)
		{
			/*
			 * Need to figure out how many more blocks are needed to given the
			 * size of the data_buf + length
			 */
			if(data_block_locations[0] != NULL)
			{
				/*
				 * Add # of new blocks to blocks_needed
				 */
				blocks_needed = (int)ceil((double)(calc_num_bytes(data_buf)+length)/BLKSIZE) + 1;
			}
			else
			{
				blocks_needed += (int)ceil((double)(length)/BLKSIZE);
			}
		}

		/* Add the data to the data_buf Break it back into blocks */
		data_block = modify_data(start, length, data_buf, mem_pointer);

		/*
		 * Check if the new write will fit onto the hard disk
		 */
		if((calc_num_free_blocks(blocks_needed + calc_index_blocks(blocks_needed-1))) == NULL)
		{
			/*
			 * Insufficient space
			 * TODO validate this error code
			 */
			print_error(INSUFFICIENT_DISK_SPACE);
			return 0;
		}

		/* Update the file size */
		inode_write.file_size = blocks_needed-1;

		i = 0;

		data_location = (uint32_t*) calloc(blocks_needed-1, sizeof(uint32_t));

		/*
		 * Write the data
		 * Check if the file needs to be encrypted
		 * 	- If it needs to be encrypted, encrypt the file
		 * Store the file into the block(s)
		 */
		while(i < blocks_needed -1)
		{
			/* Get data_blocks */
			data_location[i] = get_free_block();
			retval = write_block(data_location[i], data_block[i]);

			if(retval != 0)
			{
				/* Error occurred, reset the FBL in memory with FBL from disk */
				if(reset_fbl() == NULL)
				{
					/*
					 * TODO validate this error code
					 */
					print_error(ERROR_UPDATING_FBL);
					return -1;
				}

				/*
				 * TODO validate this error code
				 */
				print_error(DISK_WRITE_ERROR);
				return -1;
			}
			i++;
		}

		/* Rebuild the Index block */
		first_index = rebuild_index(data_location);

		if(first_index == NULL)
		{
			/* Error occurred, reset the FBL in memory with FBL from disk */
			if(reset_fbl() == NULL)
			{
				/*
				 * TODO validate this error code
				 */
				print_error(ERROR_UPDATING_FBL);
				return -1;
			}
		}

		/* Override the Inode with the new index location */
		inode_write.location = first_index;

		/* Update the Inode date last accessed and modified, then write the inode back to disk */
		cur_date = time(NULL);
		inode_write.date_last_accessed = cur_date;
		inode_write.date_last_modified = cur_date;

		buf = allocate_buf(buf, BLKSIZE);
		buf = (byte *) copy_to_buf((byte *) &inode_write, (byte *) buf, sizeof(inode_write), BLKSIZE);

		retval = write_block(inode_loc, buf);
		free(buf);

		/* Check if an error occurred writing the Inode to disk */
		if(retval != 0)
		{
			/* Error occurred, reset the FBL in memory with FBL from disk */
			if(reset_fbl() == NULL)
			{
				/*
				 * TODO validate this error code
				 */
				print_error(ERROR_UPDATING_FBL);
				return -1;
			}
		}

		if(update_fbl(NULL, data_block_locations) == NULL)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}

		if(update_fbl(NULL, old_index_block) == NULL)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}

		/* Synchronize the FBL, write the FBL in memory to disk */
		if (sync_fbl() == NULL)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}

		/**
		 * Calculate the number of free blocks
		 */
		fbl =  calc_total_free_blocks();
		if(fbl == NULL)
		{
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}
		k = 0;
		while(fbl[k] != NULL)
		{
			k++;
		}
		/**
		 * Display the number of free blocks
		 */
		printf("Total Free Blocks = %d\n", k);
		/*
		 * return value > 0 if write was successful
		 * return value <= 0 then the write was a fail
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}
	/*
	 * Invalid file descriptor OR write past EOF
	 * TODO split this into two different returns/error codes
	 * TODO validate this error code
	 */
	/* print_error(INVALID_FILE_DESCRIPTOR);
	 * print_error(FILE_PAST_EOF);
	 */
	return 0;
}
