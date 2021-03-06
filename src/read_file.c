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


int sfs_read(int fd, int start, int length, byte *mem_pointer)
{
	inode file_inode = get_null_inode();
	uint32_t index_block = 0;
	uint32_t inode_location = 0;
	locations data_blocks = NULL;
	byte* data_buf = NULL;
	uint32_t start_block = NULL;
	uint32_t i = 0;
	byte* temp = NULL;

	if(fd >= 0 && fd < NUMOFL && start >= 0 && length > 0)
	{
		/*
		 * Validate the file descriptor on the system-wide-open file table
		 */
		if (validate_fd(fd) < 0)
		{
			print_error(INVALID_FILE_DESCRIPTOR);
			return 0;
		}

		/*
		 * Use the offset to find the start of where to read in the block
		 * Read the specified bytes of the given length into the buffer
		 */

		/* Get Inode - check that it is a file */
		file_inode = get_swoft_inode(fd);

		if(file_inode.type != 0)
		{
			print_error(INVALID_FILE_TYPE);
			return 0;
		}
		/* Get index block */
		index_block = file_inode.location;

		data_blocks = iterate_index(index_block, NULL);

		if (data_blocks == NULL || data_blocks[0] == NULL)
		{
			/*
			 * File is empty
			 */
			print_error(FILE_EMPTY);
			return 0;
		}

		data_buf = get_data(data_blocks);

		/* Count the number of data blocks */
		if(start+length > calc_num_bytes(data_buf))
		{
			/*
			 * Read past end of file
			 */
			print_error(FILE_PAST_EOF);
			return 0;
		}

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
			free(temp);
			print_error(DISK_WRITE_ERROR);
			return 0;
		}
		free(temp);

		/*
		 * return value > 0 if the file was read successfully
		 * return value <= 0 if the file was read unsuccessfully
		 */
		print_error(SUCCESS);
		return 1;
	}

	/*
	 * Invalid file descriptor OR file_past_eof
	 */
	return 0;
}
