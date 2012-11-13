/**
 * Initialize the hard disk bytes to 0 
 * Pre-defined block size
 * Pre-defined bytes per block
 * Initialize the super block
 *    Create structs
 *    Save the structs
 **/

#include "blockio.h"

static void initialize(int erase)
{
	if (erase == 1)
	{
		init_disk();
	}

	/*Initialize the Superblock struct*/

}
