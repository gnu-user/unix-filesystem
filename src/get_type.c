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


#include "blockio.h"
#include "traverse_tree.h"
#include "get_type.h"


int sfs_gettype(char *pathname)
{
	uint32_t* inode_location = NULL;
	char** tokens = NULL;

	/* Parse the pathname */
	tokens = tokenize_path(pathname);

	if(tokens == NULL)
	{
		/*
		 * Invalid path name
		 * TODO validate this error code
		 */
		print_error(INVALID_PATH);
		return 0;
	}

	/* Traverse the file system to find the desired inode */
	inode_location = traverse_file_system(tokens, false);

	if(inode_location == NULL)
	{
		/*
		 * Invalid path or file/directory not found
		 * TODO validate this error code
		 */
		print_error(FILE_NOT_FOUND);
		return -1;
	}

	/*
	 * Retrieve the file type from the Inode
	 * return the file type from the Inode
	 *
	 * TODO validate this error code
	 * TODO make this use proper error handling
	 */
	print_error(SUCCESS);
	return get_type(inode_location[0]);
}
