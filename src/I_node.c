/**
 * The structures used for the Inode component of the file system:
 *
 * (Char [7]) The file name contains the user name given to the file
 * or directory, it will take up 6 bytes and limited to 6 characters
 * (Boolean) File type identifies whether the index file points to
 * file (0) or a directory (1) which will take up 1 byte.
 * (Boolean) File permissions is whether the file has read, write
 * executable which will take up 4 bytes.
 * (Integer) File created date stores the date the file was created
 * on, and will take up 4 bytes.
 * (Integer) File last accessed date stores the date the file was
 * last accessed on, and will take up 4 bytes.
 * (Integer) File last modified date stores the date the file was
 * last modified on, and will take up 4 bytes.
 * (Integer) File owner stores the user's unique identifier, taking
 * up 4 bytes.
 * (Integer) Last modified stores the unique identifier of the user
 * to last modify the file, and it will take up 4 bytes.
 * (Short Integer) File size stores size of the file, and will take
 * up 2 bytes.
 * (Pointer) Location stores the address of the block on disk, and
 * will take up 4 bytes.
 * (Boolean) The encrypted identifier will identities whether the
 * file is encrypted and will take up 1 byte.
 * (Integer) The check sum of the data (taken before it is
 * encrypted) will take up 4 bytes.
 **/
#include "I_node.h"
#include "block_func.h"

inode get_null_inode()
{
	inode i = {
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
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return *((inode*) buf)->uuid;
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
	/**
	 * Check if the type is a file
	 */
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
	/**
	 * Check if the type is a file
	 */
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
	while(index_blocks[i] != NULL)
	{
		if(strcmp(get_name(index_blocks[i]),name)==0)
		{
			return index_blocks[i];
		}
		i++;
	}
	return 0;
}

int link_inode_to_parent(uint32_t parent_location, uint32_t inode_location)
{
	/**
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
	locations loc_buf = iterate_index(parent->location, NULL);
	loc_buf = (locations) concat_len(loc_buf, &inode_location, sizeof(uint32_t), sizeof(uint32_t));

	first_index = rebuild_index(loc_buf);

	parent->location = first_index;

	buf = allocate_buf(buf, BLKSIZE);

	/**
	 * Copy the parent into to buffer
	 */
	buf = (byte *) copy_to_buf((byte *) parent, (byte *) buf, sizeof(inode),
			BLKSIZE);
	return write_block(parent_location, buf);
}

int unlink_inode_from_parent(uint32_t parent_location, uint32_t inode_location)
{
	//TODO rebuild_index NEEDS TO TAKE A SERIES OF DATA BLOCK LOCATIONS AND MAKE AN INDEX OUT OF THEM
	/**
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
