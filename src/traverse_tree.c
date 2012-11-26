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
#include "traverse_tree.h"
#include "super_block.h"

uint32_t* traverse_file_system(char** tokens, bool create)
{
	int root_dir;
	locations inode_location = (uint32_t *) calloc(2, sizeof(uint32_t));
	locations index_block = NULL;
	int index;
	int second_last = 0;
	int i = 1;

	/**
	 * Retrieve the Superblock.
	 * 	- Retrieve the root's Inode location
	 */
	root_dir = get_root();

	/**
	 * Get the root's index block location
	 */
	index = get_index_block(root_dir);

	/**
	 * Retrieve list of contents in the root directory
	 * Iterate through the contents of the root directory and locate the
	 * directory or file that is found at the first index of the path parsed.
	 */
	index_block = iterate_index(index, NULL);
	if(index_block == NULL)
	{
		/**
		 * Failed to iterate root directory
		 * TODO validate this error code
		 */
		print_error(INDEX_ALLOCATION_ERROR);
		return NULL;
	}

	/*
	 * IF index_block[0] == NULL, aka no children yet
	 *
	 */
	if(index_block[0] == NULL || tokens[0] == NULL)
	{
		if(tokens[0] != NULL)
		{
			if(create == false)
			{
				/**
				 * Invalid directory
				 * TODO validate this error code
				 */
				print_error(INVALID_PATH);
				return NULL;
			}
		}
		else
		{
			inode_location[0] = root_dir;
			inode_location[1] = 0;
			return inode_location;
		}
	}

	/**
	 * Create a function that will go through the locations from the index block
	 * and check if a given file/directory is contained
	 */

	//tokens[0] cannot be null unless something messed up, since you cannot open
	//up a file with a path that only contains '/'
	inode_location[0] = find_inode(index_block, tokens[0]);

	if(inode_location[0] == 0 && create == true || tokens[1] == NULL && create == true)
	{
		inode_location[1] = 0;
		inode_location[0] = root_dir;

		/**
		 * Inode is root
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return inode_location;
	}

	if(create == true)
	{
		inode parent = *get_inode(inode_location[0]);
		if(parent.type == 0)
		{
			/**
			 * Invalid Path, cannot use file as a directory
			 * TODO validate this error code
			 */
			print_error(INVALID_FILE_TYPE);
			return NULL;
		}
		second_last = 1;
	}

	/**
	 * General structure of the traversal:
	 * 	- From Inode get index block location
	 * 	- From index block get locations
	 * 	- Compare locations with pathname's next entry
	 * 	Loop again...
	 * Errors thrown are:
	 * 	- File not found
	 * 	- Invalid pathway (directory not found)
	 */
	while(tokens[i+second_last] != NULL)
	{
		index_block = 0;

		/**
		 * get the list of locations from the index block
		 */

		index = get_index_block(inode_location[0]);

		/**
		 * index block is empty
		 */
		index_block = iterate_index(index, NULL);

		if(index_block == NULL)
		{
			/**
			 * No Children found
			 * TODO validate this error code
			 */
			print_error(INDEX_ALLOCATION_ERROR);
			return NULL;
		}

		/**
		 * Find the inode with the given name, the current token
		 */
		inode_location[0] = find_inode(index_block, tokens[i]);

		/**
		 * Inode not found, aka file/directory not found
		 */
		if (inode_location[0] == NULL)
		{
			/**
			 * Child not found
			 * TODO validate this error code
			 */
			print_error(FILE_NOT_FOUND);
			return NULL;
		}
		i++;
	}
	inode_location[1] = i;

	/**
	 * Success
	 * TODO validate this error code
	 */
	print_error(SUCCESS);
	return inode_location;
}
