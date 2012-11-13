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

static int initialize()
{
	char null_block[BLKSIZE];

	/*Create Null Block*/
	for (int i = 0; i < BLKSIZE; i++)
	{
		null_block[j] = '0';
	}

	/*Set every block to null*/
	for(int i = 0; i < NUMBLKS; i++)
	{
		put_block(i, null_block);
	}

	/*Initialize the Superblock struct*/
}