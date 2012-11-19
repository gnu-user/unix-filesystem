/**
 * Initialize the hard disk bytes to 0 
 * Pre-defined block size
 * Pre-defined bytes per block
 * Initialize the super block
 **/

#include "blockio.h"
#include <stdio.h>
#include <stdbool.h>
#include "super_block.h"

#define SUPER_BLOCK	  0
#define FREE_BLOCK 3
#define FREE_INDEX 2
#define ROOT_DIR 2

/**
 * Initialize the superblock for the file system.
 * @param erase integer, Determines whether or not to delete the contents of the
 * file system
 * If this value is 1 then it will erase every block on the disk and then
 * re-create the super block, free block list blocks and the root directory.
 * If the value is 0 then it will re-create the super block, the free block
 * list blocks and the root directory.
 *
 * @return an integer value,
 * If the value > 0 then the initialization was successful
 * If the value <= 0 then the initialization failed
 */
int sfs_initialize(int erase)
{
	byte* buf = NULL;
	int root_dir = 0;
	int retval = 0;

	if (erase == 1 || erase == 0)
	{
		if (erase == 1)
		{
			/**
			 * Erase Disk and reallocate to free block list
			 */
			retval = wipe_disk();

			if(retval != 0)
			{
				return retval;
			}
		}

		/**
		 * Initialize the Superblock struct with a pointer to the free block
		 * list block, a pointer to the root directory Inode block.
		 **/

		root_dir = (int)(ceil(NUMBLKS/BLKSIZE))+1;
		superblock sb = { NUMBLKS*BLKSIZE, BLKSIZE, FREE_INDEX, root_dir, 0, NULL};

		/**
		 * Allocate a buffer to write to the block.
		 */
		buf = allocate_buf(buf, BLKSIZE);

		/**
		 * Copy the superblock into to buffer
		 */
		buf = (byte *) copy_to_buf((byte *)&sb, (byte *)buf, sizeof(sb), BLKSIZE);
		retval = put_block(SUPER_BLOCK, buf);

		if(retval != 0)
		{
			return retval;
		}

		/**
		 * Initialize the free_block list starting at the third index after the
		 * super block and the journal
		 **/
		retval = free_block_init();

		if(retval != 0)
		{
			return retval;
		}

		/**
		 * Initialize the root directory. This will be the first block
		 * initialized outside of the super block. The root_dir will contain an
		 * Inode that points to a index block that is empty.
		 *
		 * Have to make sure that this is writing to the block that we have
		 * determined that it will write to (aka the first block after the last
		 * block in the free block list blocks.
		 **/
		retval = sfs_create('/', 1);

		if(retval <= 0)
		{
			return retval;
		}


		buf = allocate_buf(buf, BLKSIZE);

		retval = get_block(SUPER_BLOCK, buf);

		if(retval != 0)
		{
			return retval;
		}

		/**
		 * Retrieve the super block
		 */
		superblock* super = get_super_block();

		/**
		 * Display the super block
		 */
		printf("size of disk, %d\n", super->size_of_disk);
		printf("block size, %d\n", super->block_size);
		printf("free_block_list, %d\n", super->free_block_list);
		printf("root dir, %d\n", super->root_dir);
		printf("device id, %d\n", super->device_id);

		return 1;
	}
	else
	{
		perror("sfs_initialize only excepts values 0 or 1");
		return -1;
	}

}

/**
 * Allocate all of the blocks to the free block list
 *
 * @return a integer value
 * if the free block init fails the value will be -1
 * otherwise it will be 0
 */
int free_block_init(void)
{
	bool freeblock[BLKSIZE];
	byte* buf = NULL;
	int retval = 0;

	//Divide the blocks array up into multiple
	int num_free_block = (int)(ceil(NUMBLKS/BLKSIZE));

	/**
	 * Add support for free block list index block.
	 */
	int* index_block = NULL;
	index_block = (int*) calloc(num_free_block, sizeof(int));

	for(int j = 0; j < num_free_block; j++)
	{
		for(int i = 0; i < BLKSIZE; i++)
		{
			freeblock[i] = false;

			/**
			 * Initializes the super block, journal blocks, free block list
			 * blocks, root directory Inode block, root directory index block
			 */
			if(i < num_free_block+FREE_BLOCK+ROOT_DIR && j == 0)
			{
				freeblock[i] = true;
			}
		}

		/**
		 * Add block pointer to index
		 */
		index_block[j] = FREE_BLOCK+j;

		/**
		 * Allocate a buffer to write to the block.
		 */
		buf = allocate_buf(buf, BLKSIZE);

		/**
		 * Copy the boolean array into to buffer
		 */
		buf = copy_to_buf((byte*)freeblock, buf, sizeof(freeblock), BLKSIZE);

		/**
		 * Store the buffer onto the disk.
		 */
		retval = put_block(FREE_BLOCK+j, buf);
		if(retval != 0)
		{
			return retval;
		}
	}
	buf = allocate_buf(buf, BLKSIZE);

	/**
	 * Copy the boolean array into to buffer
	 */
	buf = copy_to_buf((byte*)index_block, buf, num_free_block*sizeof(int), BLKSIZE);

	/**
	 * Store the buffer onto the disk.
	 */
	retval = put_block(FREE_INDEX, buf);
	if(retval != 0)
	{
		return retval;
	}

	return 0;
}

/**
 * Wipes the drive block by block
 *
 * @return a integer value
 * if the free block init fails the value will be -1
 * otherwise it will be 0
 */
int wipe_disk(void)
{
	//Create the null block of data
	byte* buffer = NULL;

	buffer = allocate_buf(buffer, BLKSIZE);

	int retval = 0;

	//Go block to block setting them to null
	for(int i = 0; i < NUMBLKS; i++)
	{
		retval = put_block(i, buffer);
		if(retval != 0)
		{
			return retval;
		}
	}
	return 0;
}
