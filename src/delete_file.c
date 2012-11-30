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
#include "free_block_list.h"
#include "system_open_file_table.h"
#include "delete_file.h"


int sfs_delete(char *pathname)
{
	char** tokens;
	uint32_t* parent_location = NULL;
	locations index_block = {NULL};
	locations inode_loc = (locations) calloc(2, sizeof(uint32_t));
	int type = -1;

	if(strlen(pathname) == 1)
	{
		print_error(INVALID_PATH);
		return -1;
	}

	/*
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		print_error(INVALID_PATH);
		return 0;
	}

	/*
	 * Traverse the file system to find the desired inode
	 * get the inode above the one you desired
	 */
	parent_location = traverse_file_system(tokens, true);

	if(parent_location == NULL)
	{
		/*
		 * Parent not found
		 */
		print_error(PARENT_NOT_FOUND);
		return -1;
	}

	/*if (parent_location[0] = get_root() && tokens[parent_location[1]] == NULL)
	{
		print_error(INVALID_PARAMETER);
		return -1;
	}*/

	index_block = iterate_index(get_index_block(parent_location[0]), NULL);
	if(index_block == NULL)
	{
		/*
		 * Empty or no index block
		 */
		print_error(INDEX_ALLOCATION_ERROR);
		return 0;
	}

	/*
	 * Find the inode of the file or directory with the given file name in the
	 * given index block list
	 */
	inode_loc[0] = find_inode(index_block, tokens[parent_location[1]]);

	if(inode_loc[0] == NULL)
	{
		/*
		 * Inode not found
		 */
		print_error(FILE_NOT_FOUND);
		return 0;
	}

	/*
	 * Check if it is a directory
	 */
	type = get_type(inode_loc[0]);


	index_block = iterate_index(get_index_block(inode_loc[0]), NULL);

	if(index_block == NULL)
	{
		/*
		 * Invalid index block
		 */
		print_error(INDEX_ALLOCATION_ERROR);
		return -1;
	}

	if (type == 1)
	{
		if(index_block[0] != NULL)
		{
			/*
			 * Directory has children
			 */
			print_error(DIRECTORY_HAS_CHILDREN);
			return 0;
		}
	}

	/*
	 * Delete all swoft entries for the given file
	 */
	printf("Number swoft entries remove: %d\n",find_and_remove(inode_loc[0]));

	if(unlink_inode_from_parent(parent_location[0], inode_loc[0]) < 0)
	{
		if(reset_fbl() == NULL)
		{
			print_error(ERROR_UPDATING_FBL);
			return -2;
		}

		print_error(ERROR_BLOCK_LINKAGE);
		return -1;
	}

	else if(type == 0)
	{
		/*
		 * Delete the data blocks (each time update the free_block list)
		 */
		if(update_fbl(NULL, index_block) == NULL)
		{
			print_error(ERROR_UPDATING_FBL);
			return -1;
		}
	}

	/*
	 * Delete the index blocks (each time update the free_block list)
	 */
	if(update_fbl(NULL, index_block_locations(get_index_block(inode_loc[0]), NULL)) == NULL)
	{
		print_error(ERROR_UPDATING_FBL);
		return -1;
	}

	/*
	 * Delete the Inode block (update the free_block list)
	 */
	if(update_fbl(NULL, inode_loc) == NULL)
	{
		print_error(ERROR_UPDATING_FBL);
		return -1;
	}

	/*
	 * Sync FBL, write FBL in memory to disk
	 */
	if(sync_fbl() == NULL)
	{
		print_error(ERROR_UPDATING_FBL);
		return -1;
	}

	/*
	 * return value > 0 then the file was deleted successfully.
	 * return value <= 0 then the file failed to be delete.
	 */
	print_error(SUCCESS);
	return 1;
}
