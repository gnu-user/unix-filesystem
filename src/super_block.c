#include "super_block.h"
#include "block_func.h"

superblock* get_super_block(void)
{
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
	byte* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return retval;
	}

	return ((superblock*) buf)->free_block_list;
}

int calc_uuid()
{
	//TODO make calc_uuid
	return 1;
}

int validate_uuid()
{
	//TODO make validate_uuid
	return 1;
}

