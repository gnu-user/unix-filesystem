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
		init_disk();
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

	free_block_init();
}

//Allocate all of the blocks to the free block list
void free_block_init(void)
{
	freeblock fb;

	//Divide the blocks array up into multiple
	//fb.blocks[BLKSIZE];
	int num_free_block = (int)(floor(NUMBLKS/BLKSIZE));
	for(int j = 0; j < num_free_block; j++)
	{
		for(int i = num_free_block; i < BLKSIZE; i++)
		{
			fb.blocks[i]= false;
		}
		put_block(1+j, fb->blocks);
	}

}
