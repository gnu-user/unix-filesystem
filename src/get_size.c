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
#include "blockio.h"
#include "traverse_tree.h"
#include "get_size.h"


int sfs_getsize(char *pathname)
{
	int type = -1;
	int i = 1;
	uint32_t index_block = 0;
	locations inode_location = NULL;
	locations index_locations = NULL;
	char** tokens = NULL;
	int size = 0;

	/* TODO make large if for type check */
	/* Parse the pathname */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		/* Invalid pathname
		 * TODO validate this error code
		 */
		print_error(INVALID_PATH);
		return -1;
	}

	/* Traverse the file system to find the desired inode */
	inode_location = traverse_file_system(tokens, false);

	if(inode_location == NULL)
	{
		/* Invalid path or file/directory not found
		 * TODO validate this error code
		 */
		print_error(FILE_NOT_FOUND);
		return -1;
	}

	/*
	 * Check if it is a file or directory
	 * 	- If directory:
	 * 		Count entries
	 * 	- If file:
	 * 		get size
	 */
	type = get_type(inode_location[0]);

	index_locations = index_block_locations(inode_location[0], NULL);

	if(index_locations == NULL)
	{
		/*
		 * Invalid index block
		 * TODO validate this error code
		 */
		print_error(INDEX_ALLOCATION_ERROR);
		return -1;
	}

	/*
	 * Count the number of index blocks
	 */
	while(index_locations[i+1] != NULL)
	{
		i++;
	}

	/* Add the inode */
	i++;

	/* print out the number of index blocks + the inode block */
	printf("Overhead Size =  %d\n", i*BLKSIZE);

	if(type == 0)
	{
		/* Get the size of the file from the Inode return the
		 * size of the file
		 */
		size =  get_size(inode_location[0]);
		printf("Data Size = %d\n", size);
		return size;
	}
	else if(type == 1)
	{
		/* Get the index block's location */
		index_block = get_index_block(inode_location[0]);

		/* Return the number of locations found in the index block(s) */
		size = count_files_in_dir(index_block);
		printf("Size = %d\n", size);

		print_error(SUCCESS);
		return size;
	}
	/*
	 * TODO validate this error code
	 */
	print_error(INVALID_FILE_TYPE);
	return -1;
}
