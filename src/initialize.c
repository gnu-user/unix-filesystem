/**
 * Initialize the hard disk bytes to 0 
 * Pre-defined block size
 * Pre-defined bytes per block
 * Initialize the super block
 *    Create structs
 *    Save the structs
 **/

#include "blockio.h"
#include <stdlib.h>
#include <stdbool.h>
#include "super_block.h"

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512

#define SUPER_BLOCK	  0
#define FREE_BLOCK 2

/**
 * Initializes the disk.
 * @param erase int,
 * If this value is 1 then it will erase every block
 * on the disk and then re-create the super block,
 * free block list blocks and the root directory.
 * If the value is 0 then it will re-create the
 * super block, the free block list blocks and the
 * root directory.
 */
int sfs_initialize(int erase)
{
	if (erase == 1 || erase == 0)
	{
		if (erase == 1)
		{
			/**
			 * Erase Disk and reallocate to free block list
			 */
			wipe_disk();
		}

		/**
		 * Initialize the Superblock struct with a pointer to the
		 * free block list block, a pointer to the root directory
		 * Inode block.
		 **/

		int root_dir = (int)(floor(NUMBLKS/BLKSIZE))+1;
		superblock sb = { NUMBLKS*BLKSIZE, BLKSIZE, FREE_BLOCK, root_dir, 0};

		//put_block(1, sb.information);

		/**
		 * Initialize the free_block list starting at the third index
		 * after the super block and the journal
		 **/
		free_block_init();

		/**
		 * Initialize the root directory. This will be the first block
		 * initialized outside of the super block
		 **/

		/**
		 * root_dir will contain an Inode that points to a index block
		 * that is empty.
		 *
		 * Have to make sure that this is writing to the block that we
		 * have determined that it will write to (aka the first block
		 * after the last block in the free block list blocks.
		 **/
		//sfs_create('/', 1)
		return 0;
	}
	else
	{
		perror("sfs_initialize only excepts values 0 or 1");
		return -1;
	}

}

/**
 * Allocate all of the blocks to the free block list
 */
void free_block_init(void)
{
	bool freeblock[BLKSIZE];

	//Divide the blocks array up into multiple
	int num_free_block = (int)(floor(NUMBLKS/BLKSIZE));

	for(int i = 0; i < num_free_block+FREE_BLOCK;i++)
	{
		freeblock[i] = true;
	}
	for(int j = 0; j < num_free_block; j++)
	{
		for(int i = num_free_block+FREE_BLOCK; i < BLKSIZE; i++)
		{
			freeblock[i] = false;
		}
		/**
		 * It might not work because it is expecting a char* but is
		 * given a bool. Might be better just to store a char 0 or 1
		 */
		put_block(FREE_BLOCK+j, freeblock);
	}
}

/**
 * Wipes the drive block by block
 */
void wipe_disk(void)
{
	//Create the null block of data
	char* buffer = calloc(128, sizeof(char));

	//Go block to block setting them to null
	for(int i = 0; i < NUMBLKS; i++)
	{
		put_block(i, buffer);
	}
}
