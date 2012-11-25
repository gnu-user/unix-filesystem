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
#include "index_block.h"
#include <math.h>
#include <stdbool.h>

uint32_t FBL_DATA_SIZE;
uint32_t FBL_TOTAL_SIZE;
uint32_t ROOT;

int sfs_initialize(int erase) {
	//TODO finish create
	FBL_DATA_SIZE = ceil((double)(NUMBLKS / BLKSIZE));
	FBL_TOTAL_SIZE = (uint32_t) ceil(
			FBL_DATA_SIZE / (floor(BLKSIZE / (double)(sizeof(uint32_t))) - 1))
			+ FBL_DATA_SIZE;
	ROOT = (uint32_t) (FBL_INDEX + FBL_TOTAL_SIZE);
	byte* buf = NULL;
	int root_dir = 0;
	int retval = 0;
	char root_name[] = "/";
	int variant = 0;
	char str[100];

	if (erase == 1 || erase == 0) {
		if (erase == 1) {
			/**
			 * Erase Disk and reallocate to free block list
			 */
			retval = wipe_disk();

			if (retval != 0) {
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

		superblock sb = { NUMBLKS * BLKSIZE, BLKSIZE, FBL_INDEX, ROOT, 0, NULL,
				0 };

		uuid_generate(sb.uuid);

		/**
		 * Allocate a buffer to write to the block.
		 */
		buf = allocate_buf(buf, BLKSIZE);

		/**
		 * Copy the superblock into to buffer
		 */
		buf = (byte *) copy_to_buf((byte *) &sb, (byte *) buf, sizeof(sb),
				BLKSIZE);
		retval = write_block(SUPER_BLOCK, buf);
		free(buf);

		if (retval != 0) {
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

		if (retval != 0) {
			return retval;
		}

		/**
		 * Initialize the root directory. This will be the first block
		 * initialized outside of the super block. The root_dir will contain an
		 * Inode that points to a index block that is empty.
		 **/
		retval = sfs_create(root_name, 1);

		/*char databuf_1[50];

		for(int i = 0; i < 49; i++)
		{
			databuf_1[i] = '1';
		}
		databuf_1[49] = NULL;
		char data_buf_2[150] = {1};
		for(int i = 0; i < 149; i++)
		{
			data_buf_2[i] = '2';
		}
		data_buf_2[149] = NULL;
		char data_buf_3[300] = {1};
		for(int i = 0; i < 299; i++)
		{
			data_buf_3[i] = '3';
		}
		data_buf_3[299] = NULL;

		char data_buf_4[500] = {1};
		for(int i = 0; i < 499; i++)
		{
			data_buf_4[i] = '4';
		}
		data_buf_4[499] = NULL;

		printf("Number of Blocks 50, %d\n", calc_num_bytes(databuf_1));
		printf("Number of Blocks 150, %d\n", calc_num_bytes(data_buf_2));
		printf("Number of Blocks 300, %d\n", calc_num_bytes(data_buf_3));
		printf("Number of Blocks 500, %d\n", calc_num_bytes(data_buf_4));*/

		if (retval <= 0) {
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return retval;
		}

		/**
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	} else {
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
	block* data_blocks = NULL;
	uint32_t i = 0;

	/* Initialize the new FBL in memory, mark the superblock as used */
	fbl = update_fbl(NULL, NULL );
	if (fbl == NULL )
	{
		//TODO return SUCCESS/FAIL enum
		/* Error occurred updating the FBL in memory */
		return -1;
	}

	/* Write the new FBL to disk */
	//First write the index.
	idx = generate_index(FBL_DATA_SIZE);

	//Now write the data blocks.

	//Segment the data blocks and write them at the locations set aside by the index.

	data_blocks = segment_data_len(fbl, NUMBLKS);

	/* Check that the data_blocks were segmented properly */
	if (data_blocks == NULL)
	{
		//TODO return SUCCESS/FAIL enum
		/* Error occurred segmenting the data blocks */
		return -1;
	}

	while (idx.data_locations[i] != NULL)
	{
		write_block(idx.data_locations[i], data_blocks[i]);
		i++;
	}

	/* LINKING THE NEW FBL TO SUPERBLOCK ALREADY HAPPENED
	 * 	VERIFY idx.indexlocation = the superblock's fbl location
	 */

	//TODO return SUCCESS/FAIL enum
	return 0;
}

int wipe_disk(void) {
	/**
	 * Create the null block of data
	 */
	byte* buffer = NULL;

	buffer = allocate_buf(buffer, BLKSIZE);

	int retval = 0;

	/**
	 * Go block to block setting them to null
	 */
	for (uint32_t i = 0; i < NUMBLKS; i++) {
		retval = write_block(i, buffer);
		if (retval != 0) {
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
