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


#include "super_block.h"
#include "block_func.h"

superblock* get_super_block(void)
{
	//TODO FIX MEMORY LEAK
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return (superblock*) buf;
}

uint32_t get_root(void)
{
	//TODO FIX MEMORY LEAK
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return retval;
	}

	return ((superblock*) buf)->root_dir;
}

uint32_t get_free_block_index(void)
{
	//TODO FIX MEMORY LEAK
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return retval;
	}

	return ((superblock*) buf)->free_block_list;
}

int display_super_block(void)
{
	//Retrieve the super block
	superblock* super = get_super_block();

	if(super == NULL)
	{
		return 0;
	}

	//Display the super block
	printf("size of disk, %d\n", super->size_of_disk);
	printf("block size, %d\n", super->block_size);
	printf("free_block_list, %d\n", super->free_block_list);
	printf("root dir, %d\n", super->root_dir);
	printf("device id, %d\n", super->device_id);

	return 1;
}

/*int validate_uuid()
{
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return retval;
	}

	((superblock*) buf)->uuid;
	return 1;
}*/

