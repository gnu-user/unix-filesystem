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


#include "I_node.h"
#include "block_func.h"

inode get_null_inode()
{
	/* Initialize an empty/NULL Inode */
	inode i =
	{
		.name = "",
		.type = false,
		.read = true,
		.write = true,
		.execute = true,
		.date_of_create = 0,
		.date_last_accessed = 0,
		.date_last_modified = 0,
		.file_owner = 0,
		.last_user_modified = 0,
		.file_size = 0,
		.location = 0,
		.encrypted = false,
		.check_sum = 0,
		.uuid = NULL
	};
	uuid_generate(i.uuid);
	return i;
}


inode* get_inode(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return (inode*) buf;
}


unsigned char* get_uuid(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}

	return &((inode*) buf)->uuid;
}


uint32_t get_index_block(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->location;
}


int get_type(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->type;
}


uint32_t get_size(uint32_t block_num)
{
	/* Check if the type is a file */
	if (get_type(block_num) != 0)
	{
		return -1;
	}
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->file_size;
}


int get_encrypted(uint32_t block_num)
{
	/* Check if the type is a file */
	if(get_type(block_num) != 0)
	{
		return 0;
	}

	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->encrypted;
}


char* get_name(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return ((inode*) buf)->name;
}


uint32_t get_crc(uint32_t block_num)
{
	//TODO FIX MEMORY LEAK
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return ((inode*) buf)->check_sum;
}


uint32_t find_inode(locations index_blocks, char* name)
{
	int i = 0;
	uint32_t inode_name_len = 0;

	while(index_blocks[i] != NULL)
	{
		/* Do not perform a string comparison unless both are the same length */
		inode_name_len = strlen(get_name(index_blocks[i]));
		if (inode_name_len == strlen(name))
		{
			if(strncmp(get_name(index_blocks[i]), name, inode_name_len) == 0)
			{
				return index_blocks[i];
			}
		}
		i++;
	}
	return 0;
}


int link_inode_to_parent(uint32_t parent_location, uint32_t inode_location)
{
	/*
	 * Gets the parent's index
	 * locations_buf = iterate the index (parent_index)
	 * //add's the inode location of the child to the end of the buffer
	 * locations_buf += child's inode
	 * rebuilds_index(locations_buf)
	 * link the new index block's location to the parent inode
	 */
	uint32_t first_index = NULL;
	byte* buf = NULL;
	inode* parent = get_inode(parent_location);
	uint32_t pre_index = parent->location;
	locations free_blocks = NULL;
	locations loc_buf = iterate_index(pre_index, NULL);
	loc_buf = (locations) concat_len(loc_buf, &inode_location, sizeof(uint32_t), sizeof(uint32_t));

	first_index = rebuild_index(loc_buf);

	parent->location = first_index;

	buf = allocate_buf(buf, BLKSIZE);

	/* Copy the parent into to buffer */
	buf = (byte *) copy_to_buf((byte *) parent, (byte *) buf, sizeof(inode),
			BLKSIZE);
	if(write_block(parent_location, buf) < 0)
	{
		return -1;
	}

	free_blocks = index_block_locations(pre_index, NULL);

	if(free_blocks == NULL)
	{
		return -1;
	}

	update_fbl(NULL, free_blocks);
	return 0;
}


/*
 * locations idxbuf = NULL;
 * inode parent_inode = get_inode(parent_location);
 * idx = iterate_index(parent_inode.location);
 * search idx:
 *  if idx.index = parent_inode.location
 *  	idx = remove that index
 *  	idx = shift remain indices left
 *  	newidx = rebuild_idx(idx)
 *  	parent_inode.location = newidx.first_indexlocation
 *  	write_block(parent_location, parent_inode)
 *  	return success
 * return failed // Couldn't find location to unlink in index
 */
int unlink_inode_from_parent(uint32_t parent_location, uint32_t inode_location)
{
	inode* parent_inode = get_inode(parent_location);
	inode* child_inode = get_inode(inode_location);
	locations index_block = iterate_index(parent_inode->location, NULL);
	locations new_index_block = NULL;
	uint32_t new_index_loc = NULL;
	locations free_blocks = NULL;
	byte* buf = NULL;
	uint32_t i = 0;
	uint32_t j = 0;

	if(index_block == NULL || index_block[0] == NULL)
	{
		/* Empty Index block */
		return -1;
	}

	free_blocks = index_block_locations(parent_inode->location, NULL);
	if(free_blocks == NULL)
	{
		/* Index blocks not found */
		return -1;
	}

	new_index_block = (locations) calloc(calc_num_blocks(index_block), sizeof(uint32_t));

	while(index_block[i] != NULL)
	{
		if(index_block[i] != inode_location)
		{
			/* Child not found */
			memcpy(&new_index_block[j], &index_block[i], 1);
			j++;
		}
		i++;
	}

	if(new_index_block[0] == NULL)
	{
		new_index_loc = get_free_block();
	}
	else
	{
		new_index_loc = rebuild_index(new_index_block);
	}

	if(new_index_loc == NULL)
	{
		/* Rebuild failed */
		return -1;
	}

	parent_inode->location = new_index_loc;

	buf = allocate_buf(buf, BLKSIZE);

	/* Copy the parent into the buffer */
	buf = (byte *) copy_to_buf((byte *) parent_inode, (byte *) buf, sizeof(inode), BLKSIZE);

	if(write_block(parent_location, buf) < 0)
	{
		/* Invalid write */
		return -1;
	}

	update_fbl(NULL, free_blocks);
	return 0;
}


int get_index_entry(inode directory)
{
	if(uuid_compare(cur_dir.directory.uuid, directory.uuid) != 0)
	{
		cur_dir.cur_index = 0;
		cur_dir.directory = directory;
	}
	uint32_t next = cur_dir.cur_index;
	cur_dir.cur_index++;

	return next;
}


void reset_index_entry()
{
	cur_dir.cur_index = 0;
}
