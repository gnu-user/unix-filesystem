/**
 * Initialize the hard disk bytes to 0 
 * Pre-defined block size
 * Pre-defined bytes per block
 * Initialize the super block
 **/
#include "initialize.h"
#include "block_func.h"
#include "super_block.h"
#include "free_block_list.h"
#include <math.h>
#include <stdbool.h>

int sfs_initialize(int erase)
{
	//TODO finish create
	FBL_DATA_SIZE = ceil(NUMBLKS/BLKSIZE);
	FBL_TOTAL_SIZE = (uint32_t) ceil(FBL_DATA_SIZE / (ceil(BLKSIZE/sizeof(uint32_t)) - 1)) + FBL_DATA_SIZE;
	ROOT = (uint32_t) (FBL_INDEX + FBL_TOTAL_SIZE);
	byte* buf = NULL;
	int root_dir = 0;
	int retval = 0;
	char root_name[] = "/";
	int variant =0;
	char str[100];

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
				/**
				 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
				 */
				return retval;
			}
		}

		/**
		 * Initialize the Superblock struct with a pointer to the free block
		 * list block, a pointer to the root directory Inode block.
		 **/


		superblock sb = { NUMBLKS*BLKSIZE, BLKSIZE, FBL_INDEX, ROOT, 0, NULL, 0};

		uuid_generate(sb.uuid);

		/**
		 * Allocate a buffer to write to the block.
		 */
		buf = allocate_buf(buf, BLKSIZE);

		/**
		 * Copy the superblock into to buffer
		 */
		buf = (byte *) copy_to_buf((byte *)&sb, (byte *)buf, sizeof(sb), BLKSIZE);
		retval = write_block(SUPER_BLOCK, buf);
		free(buf);

		if(retval != 0)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
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
		 **/
		retval = sfs_create(root_name, 1);

		if(retval <= 0)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return retval;
		}

		/**
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	}
	else
	{
		//perror("sfs_initialize only excepts values 0 or 1");
		/**
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

}


int free_block_init(void)
{
	data_index idx = { 0 };
	free_block_list* fbl = NULL;
	block* data_block = NULL;

	/* Initialize the new FBL in memory, mark the superblock as used */
	fbl = update_fbl(NULL,NULL);
	if (fbl == NULL)
	{
		//TODO return SUCCESS/FAIL enum
		/* Error occurred updating the FBL in memory */
		return -1;
	}

	/* Write the new FBL to disk */
	idx = generate_index(FBL_DATA_SIZE);

	uint32_t i = 0;


	/**
	 * INITIALIZE THE NEW FBL
	 * update_fbl(NULL,NULL) marks the superblock used in our formatted disk
	 *
	 * WRITE A NEW FBL TO DISK
	 * idx = generate_index(how many blocks (fbl))

		/**
		 * Write the data
		 * Check if the file needs to be encrypted
		 * 	- If it needs to be encrypted, encrypt the file
		 * Store the file into the block(s)
		 */
		while(idx.data_locations[i] != NULL)
		{
			write_block(idx.data_locations[i], fbl[i]);
			i++;
		}

	 *
	 * LINK THE NEW FBL TO SUPERBLOCK
	 * 	update the superblock to point to idx.indexlocation
	 */

	//TODO return SUCCESS/FAIL enum
	return -1;
}


int wipe_disk(void)
{
	/**
	 * Create the null block of data
	 */
	byte* buffer = NULL;

	buffer = allocate_buf(buffer, BLKSIZE);

	int retval = 0;

	/**
	 * Go block to block setting them to null
	 */
	for(uint32_t i = 0; i < NUMBLKS; i++)
	{
		retval = write_block(i, buffer);
		if(retval != 0)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return retval;
		}
	}
	free(buffer);
	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return 0;
}
