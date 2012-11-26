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
#include "index_block.h"
#include "system_open_file_table.h"
#include "read_dir.h"

/** sfs_readdir
 * Reads the file name components from a directory file. The first time
 * sfs_readdir is called, the first file name component in the directory will be
 * placed into memory at the location pointed to by mem_pointer. Each successive
 * call to sfs_readdir will place the next name component from the directory into
 * the mem_pointer buffer. When all names have been returned, sfs_readdir will
 * place nothing in the buffer, and return a value of zero to indicate the
 * directory has been completely scanned.
 *
 * @param fd A file descriptor for the file to read data from
 * @param mem_pointer The memory location to store the file name components
 *
 * @return an integer value
 * If the value > 0 the read dir was a success
 * If the value = 0 if there is no contents in dir
 * If the value < 0 the read dir was unsuccessful
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 */
int sfs_readdir(int fd, char *mem_pointer)
{
	//TODO test readdir
	inode directory = get_null_inode();
	locations index_block = NULL;
	uint32_t inode_location = 0;
	uint32_t i = 0;
	uint32_t num_locations = 0;
	int count = 0;
	byte* buf = NULL;

	if(fd >= 0 && fd < NUMOFL)
	{

		/*
		 * Validate the file descriptor
		 */
		if(validate_fd(fd) < 0)
		{
			/**
			 * file descriptor not found in swoft
			 * TODO validate this error code
			 */
			print_error(INVALID_FILE_DESCRIPTOR);
			return -1;
		}

		/*
		 * Retrieve the contents of the directory's index block. Use the Inode
		 * to retrieve the names of the contents. Store the values into
		 * mem_pointer.
		 */
		directory = get_swoft_inode(fd);

		/* If the inode is not a directory return an error */
		if(directory.type != 1)
		{
			/*
			 * Invalid file type error
			 * TODO validate this error code
			 */
			print_error(INVALID_FILE_TYPE);
			return -1;
		}

		/*
		 * Iterate through the index block
		 * TODO ensure that iterate_index returns a null value for index_block
		 * when the directory is empty
		 */
		index_block = iterate_index(directory.location, NULL);
		if(index_block == NULL)
		{
			/*
			 * Invalid index block
			 * TODO validate this error code
			 */
			print_error(INDEX_ALLOCATION_ERROR);
			return -1;
		}

		num_locations = count_files_in_dir(directory.location);

		if(num_locations < 0)
		{
			/*
			 * Invalid index block
			 * TODO validate this error code
			 */
			print_error(INDEX_ALLOCATION_ERROR);
			return -1;
		}
		int cur_index = get_index_entry(*get_inode(directory.location));

		if(num_locations == cur_index)
		{
			reset_index_entry();
			return 0;
		}


		char* test_name = get_name(index_block[cur_index]);
		strcpy(mem_pointer, test_name);

		/*
		 * return value > 0 for a successful read dir
		 * return value = 0 if there is no contents in dir
		 * return value < 0 for a unsuccessful read dir
		 */
		if(mem_pointer == NULL)
		{
			/*
			 * Empty Directory Read
			 * TODO validate this error code
			 */
			print_error(DIRECTORY_EMPTY);
			return 0;
		}

		/* Update the directory inode date last accessed and write the inode back to disk */
		directory.date_last_accessed = time(NULL);

		/* Get the inode location */
		inode_location = get_inode_loc(fd);

		buf = allocate_buf(buf, BLKSIZE);
		buf = (byte *) copy_to_buf((byte *) &directory, (byte *) buf, sizeof(inode), BLKSIZE);

		if(write_block(inode_location, buf) < 0)
		{
			/*
			 * TODO validate this error code
			 */
			free(buf);
			print_error(DISK_WRITE_ERROR);
			return -1;
		}
		free(buf);

		/*
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}

	/*
	 * TODO validate and update this error code, why does it return -1?
	 */
	print_error(UNKNOWN);
	return -1;
}
