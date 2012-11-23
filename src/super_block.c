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

