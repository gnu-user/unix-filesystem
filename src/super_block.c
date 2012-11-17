#include "super_block.h"

superblock* get_super_block(byte* buf)
{
	return (superblock*) buf;
}

int get_root(byte* buf)
{
	return ((superblock*) buf)->root_dir;
}

int get_free_block(byte* buf)
{
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

