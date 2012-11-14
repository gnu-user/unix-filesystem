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

static void initialize(int erase)
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
	 **/
	//create('/', 1)


}

//Allocate all of the blocks to the free block list
void free_block_init(void)
{
	//freeblock fb;
	bool freeblock[BLKSIZE];

	//Divide the blocks array up into multiple
	//fb.blocks[BLKSIZE];
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
		put_block(FREE_BLOCK+j, freeblock);
	}
}

static void wipe_disk(void)
{
	char* buffer = calloc(128, sizeof(char));
	for(int i = 0; i < NUMBLKS; i++)
	{
		put_block(i, buffer);
	}
}
