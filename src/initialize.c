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

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512

#define SUPER_BLOCK	  1

static void initialize(int erase)
{

	if (erase == 1)
	{
		/**
		 * Erase Disk and reallocate to free block list
		 */
		//init_disk();
		free_block_init();
	}
	else
	{
		/**
		 * Copy the root dir pointer
		 * Copy the free block list pointer
		 **/

	}

	/*Initialize the Superblock struct
	 * Create the free block list, (ever block on it)
	 * Write the root directory
	 **/

	superblock sb = { NUMBLKS*BLKSIZE, BLKSIZE, 0, 0, 0};
	//sb.root_dir = pointer;
	//sb.free_block_list = pointer2;

	char* buf;
	get_block(SUPER_BLOCK, buf);
	char*size_d = buf[0] + buf[1] + buf[2] + buf[3];
	//sb->size_of_disk = (int) buf
}

//Allocate all of the blocks to the free block list
void free_block_init(void)
{
	freeblock fb;
	fb.blocks[NUMBLKS];
	for(int i = 1; i < NUMBLKS-1; i++)
	{
		fb.blocks[i]= false;
		put_block(i, fb->blocks);
	}
}
