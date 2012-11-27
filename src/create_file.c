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
#include "super_block.h"
#include "traverse_tree.h"
#include "block_func.h"
#include "create_file.h"
#include "mount.h"
#include <string.h>
#include <time.h>


int sfs_create(char *pathname, int type)
{
	inode new_block = get_null_inode();
	char** tokens;
	locations inode_loc = NULL;
	locations index_block = NULL;
	data_index index_location = {0};
	uint32_t data_location = NULL;
	uint32_t new_inode_location[3] = {NULL, NULL, NULL};
	byte* buf = NULL;
	uint32_t i = 0;
	int parent_offset = 0;
	int retval = 0;
	time_t cur_date;
	uint32_t i = 0;
	locations fbl = NULL;

	/* Check for valid type = 0 or = 1 */
	if(type == 0 || type == 1)
	{
		/* Parse the pathname */
		tokens = tokenize_path(pathname);
		if(tokens == NULL)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(INVALID_PATH);
			return 0;
		}

		/*
		 * Traverse the file system to find the directory containing the desired
		 * inode
		 */
		if(tokens[0] != NULL)
		{
			inode_loc = traverse_file_system(tokens, true);

			/*
			 * Invalid path or path does not exist
			 */
			if(inode_loc == NULL)
			{
				/*
				 * TODO validate this error code
				 */
				print_error(INVALID_PATH);
				return 0;
			}

			/*
			 * Check if the there is another file with the given name
			 * 	- If there is another file, there is an invalid file name error
			 */
			index_block = iterate_index(get_index_block(inode_loc[0]), NULL);

			if(index_block != NULL)
			{
				/*
				 * Check File/directory already exists
				 */
				if(find_inode(index_block, tokens[inode_loc[1]]) != NULL)
				{
					print_error(INVALID_FILE_NAME);
					return 0;
				}

				i = 0;
				while(index_block[i] != NULL)
				{
					i++;
				}

				if(i % (int)(floor(BLKSIZE/sizeof(uint32_t)) - 1) == 0)
				{
					parent_offset++;
				}
			}
		}
		else
		{
			/*
			 * Validate that root has not been written
			 */
			if(validate_root_dir() == -1)
			{
				inode_loc = SUPER_BLOCK;
			}
			else
			{
				/*
				 * Cannot override root
				 * TODO validate this error code
				 */
				print_error(INVALID_PATH);
				return -1;
			}
		}

		/*
		 * Check if there is enough space on the disk for the new create
		 * (2 blocks for directory or file)
		 */
		if(calc_num_free_blocks(CREATE_SIZE + parent_offset) == NULL)
		{
			/*
			 * Not enough space
			 * TODO validate this error code
			 */
			print_error(INSUFFICIENT_DISK_SPACE);
			return -1;
		}

		/*
		 * Get a free block location for the Inode
		 */
		new_inode_location[0] = get_free_block();

		if (new_inode_location[0] == 0)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(INSUFFICIENT_DISK_SPACE);
			return 0;
		}

		/*
		 * Copy the name into the inode
		 */
		if (tokens[0] != NULL)
		{
			strcpy(new_block.name, tokens[inode_loc[1]]);
		}
		else
		{
			strncpy(new_block.name, "/", 1);
		}

		/*
		 * Fill in the information to be stored in the Inode.
		 * Initialize values depending on the file type
		 */
		if (type == 0)
		{
			new_block.type = false;
		}
		else
		{
			new_block.type = true;
			/*
			 * Identify whether the file is encrypted
			 */
			new_block.encrypted = 0;

		}

		new_block.file_size = 0;

		/* Get the current date & time in POSIX time format and set the
		 * Inode date parameters
		 */
		cur_date = time(NULL);
		new_block.date_of_create = cur_date;
		new_block.date_last_accessed = cur_date;
		new_block.date_last_modified = cur_date;

		/*
		 * Generate CRC for inode for unique identifier
		 */

		/*
		 * Create an index block empty index block
		 */
		index_location = generate_index(0);

		if(index_location.index_location == NULL)
		{
			/*
			 * De-allocate the inode
			 * TODO make sure that the new_inode_location is null terminated
			 */

			if(update_fbl(NULL, new_inode_location) == NULL)
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
			print_error(INDEX_ALLOCATION_ERROR);
			return 0;
		}

		/*
		 * Assign locations
		 * 	- Store the index block's location in the Inode block
		 * 	- Store the data block's location in the index block
		 */
		new_block.location = index_location.index_location;

		/*
		 * Store the blocks on disk
		 * 	- If there is an error while writing, de-allocate the blocks
		 * 	  return error
		 */

		buf = allocate_buf(buf, BLKSIZE);

		buf = (byte *) copy_to_buf((byte *) &new_block, (byte *)buf, sizeof(new_block), BLKSIZE);
		retval = write_block(new_inode_location[0], buf);


		if(retval != 0)
		{
			/*
			 * De-allocate the index blocks
			 */
			new_inode_location[1] = index_location.index_location;
			if(update_fbl(NULL, new_inode_location) == NULL)
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
			return 0;
		}

		/*
		 * Add the inode's location to the parent's index list
		 * If add location fails de-allocate Inode and index block
		 */
		if(tokens[0] != NULL)
		{
			if(link_inode_to_parent(inode_loc[0], new_inode_location[0]) < 0)
			{
				new_inode_location[1] = index_location.index_location;
				if(update_fbl(NULL, new_inode_location) == NULL)
				{
					//TODO validate this error code
					print_error(ERROR_UPDATING_FBL);
					return -1;
				}
				//TODO validate this error code
				print_error(ERROR_BLOCK_LINKAGE);
				return 0;
			}
		}
		free(buf);

		/*
		 * TODO update size of parent
		 */

		/* Synchronize the FBL, write the FBL in memory to disk */
		if (sync_fbl() == NULL)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}

		fbl =  calc_total_free_blocks();
		if(fbl == NULL)
		{
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}
		while(fbl[i] != NULL)
		{
			i++;
		}
		printf("Total Free Blocks = %d\n", i);
		/*
		 * return value > 0 the file create was a success
		 * return value <= 0 the file create was unsuccessful
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}
	/*
	 * TODO validate this error code
	 */
	print_error(INVALID_FILE_TYPE);
	return 0;
}
