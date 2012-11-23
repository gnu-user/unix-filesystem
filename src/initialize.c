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
				return retval;
			}
		}

		/**
		 * Initialize the Superblock struct with a pointer to the free block
		 * list block, a pointer to the root directory Inode block.
		 **/

		root_dir = (int)(ceil(NUMBLKS/BLKSIZE))+1;
		superblock sb = { NUMBLKS*BLKSIZE, BLKSIZE, FREE_INDEX, root_dir, 0, NULL, 0};

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
		 **/
		retval = sfs_create(root_name, 1);

		if(retval <= 0)
		{
			return retval;
		}

		buf = allocate_buf(buf, BLKSIZE);

		retval = read_block(SUPER_BLOCK, buf);

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
		//perror("sfs_initialize only excepts values 0 or 1");
		return -1;
	}

}


int free_block_init(void)
{
	//Divide the blocks array up into multiple
	uint32_t num_free_block = (uint32_t)(ceil(NUMBLKS/BLKSIZE));

	/**
	 * Create a list of the blocks used
	 * Create a list of blocks that are remaining
	 */
	uint32_t* used = (uint32_t *) calloc(num_free_block, sizeof(bool));

	for(uint32_t i = 0; i < num_free_block; i++)
	{
		used[i] = i;
	}

	/**
	 * Update the free block list and check if it succeeded
	 */
	if(update_fbl(used, NULL) == NULL)
	{
		return -1;
	}
	return 0;
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
			return retval;
		}
	}
	return 0;
}
