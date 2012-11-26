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
#include "index_block.h"
#include "system_open_file_table.h"
#include <math.h>
#include "read_file.h"

/** sfs_read
 * Copy the length of bytes of data specified from a regular file to memory
 * location specified by mem_pointer. The parameter start gives the offset
 * of the first byte in the file that should be copied.
 *
 * @param fd A file descriptor for the file to read data from
 * @param start The offset of the first byte in the file that should be copied
 * @param length The length of bytes of data to copy from the file
 * @param mem_pointer The memory location to store the data read from the file
 *
 * @return an integer value,
 * if the value > 0 then the file was read successfully
 * if the value <= 0 then the file was read unsuccessfully
 *
 * @exception FILE_LENGTH_OVERRUN If the file cannot be read correctly because
 * the length of bytes specified exceeds the length of the file, no data will be
 * copied from the file if an overrun occurs.
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 */
int sfs_read(int fd, int start, int length, byte *mem_pointer)
{
	//TODO test read
	//TODO create encryption
	//TODO create decryption
	inode file_inode = get_null_inode();
	uint32_t index_block = 0;
	uint32_t inode_location = 0;
	locations data_blocks = NULL;
	byte* data_buf = NULL;
	uint32_t start_block = NULL;
	uint32_t i = 0;
	byte* temp = NULL;

	//TODO split this into two error codes!!!
	if(fd >= 0 && fd < NUMOFL && start >= 0 && length > 0)
	{
		/*
		 * Validate the file descriptor on the system-wide-open file table
		 *  - If the file descriptor is not found return error
		 */
		if (validate_fd(fd) < 0)
		{
			/*
			 * TODO validate this error code
			 */
			print_error(INVALID_FILE_DESCRIPTOR);
			return 0;
		}

		/*
		 * Use the offset to find the start of where to read in the block
		 * Read the specified bytes of the given length into the buffer
		 */

		/*
		 * Get Inode
		 * 	- check that it is a file
		 */
		file_inode = get_swoft_inode(fd);

		/*
		 * Get index block
		 */
		index_block = file_inode.location;

		data_blocks = iterate_index(index_block, NULL);

		if (data_blocks == NULL || data_blocks[0] == NULL)
		{
			/*
			 * File is empty
			 * TODO validate this error code
			 */
			print_error(FILE_EMPTY);
			return 0;
		}

		data_buf = get_data(data_blocks);

		/*
		 * Since start is offset (number of bytes offset)
		 * ceil(start/BLKSIZE)
		 */

		/*
		 * Count the number of data blocks
		 */
		if(start+length > calc_num_bytes(data_buf))
		{
			/**
			 * Read past end of file
			 * TODO validate this error code
			 */
			print_error(FILE_PAST_EOF);
			return 0;
		}

		/*
		 * copy the data block at start into memory
		 * TODO figure out how to fix missing reference for ceil
		 */
		//start_block = (uint32_t)(ceil((double)(start)/BLKSIZE));

		/*
		 * data_buf = data_blocks parsed
		 * Search through data_buf for byte start where start >= 0
		 * if start+length > length(data_buf)
		 * 	return invalid read past end of file.
		 * mem_pointer = copy data_buf from start to index = start + length
		 */
		i = 0;
		while(data_buf[start+i] != NULL && i < length)
		{
			/* concat the mem_pointer */
			temp = (byte*) concat_len(mem_pointer, &data_buf[start+i], sizeof(byte), sizeof(byte));
			memcpy(mem_pointer, temp, (i+1)*sizeof(byte));
			free(temp);
			//mem_pointer = temp;
			i++;
		}

		/* Update the inode date last accessed and write the inode back to disk */
		file_inode.date_last_accessed = time(NULL);

		/* Get the inode location */
		inode_location = get_inode_loc(fd);

		temp = allocate_buf(temp, BLKSIZE);
		temp = (byte *) copy_to_buf((byte *) &file_inode, (byte *) temp, sizeof(inode), BLKSIZE);

		if(write_block(inode_location, temp) < 0)
		{
			/*
			 * TODO validate this error code
			 */
			free(temp);
			print_error(DISK_WRITE_ERROR);
			return 0;
		}
		free(temp);

		/*
		 * return value > 0 if the file was read successfully
		 * return value <= 0 if the file was read unsuccessfully
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}

	/*
	 * Invalid file descriptor OR file_past_eof
	 * TODO validate this error code
	 * TODO split this into a 2 different returns
	 */
	return 0;
}
