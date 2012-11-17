#include "super_block.h"

superblock* get_super_block(void)
{
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = get_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return (superblock*) buf;
}

int get_root(void)
{
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = get_block(SUPER_BLOCK, buf);

	if(retval != 0)
	{
		return retval;
	}

	return ((superblock*) buf)->root_dir;
}

int get_free_block_index(void)
{
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = get_block(SUPER_BLOCK, buf);

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

