/**
 * Initialize the hard disk bytes to 0 
 * Pre-defined block size
 * Pre-defined bytes per block
 * Initialize the super block
 *    Create structs
 *    Save the structs
 **/

#include "blockio.h"

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512

static void initialize(int erase)
{

	if (erase == 1)
	{
		/**
		 * Erase Disk and reallocate to free block list
		 */
		init_disk();
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

	/*super_block sb;

	sb->block_size = BLKSIZE;
	sb->size_of_disk = NUMBLKS*BLKSIZE;
	sb->root_dir = pointer;
	sb->free_block_list = pointer2;
	sb->device_id = 0;
	*/
}

//Allocate all of the blocks to the free block list
void free_block_init(void)
{
	for(int i = 1; i < NUMBLKS-1; i++)
	{
		char* pointer = (char*)i+1;
		put_block(i, pointer);
	}
}
