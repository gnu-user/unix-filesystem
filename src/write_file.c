#include "glob_data.h"
#include "block_func.h"
#include "I_node.h"
#include "system_open_file_table.h"
#include "index_block.h"
#include <math.h>

/**
 *
 * TODO THIS NEEDS TO BE FIXED, FOR DYNAMICALLY ALLOCATING THE 2D ARRAY!!!!
 *
 * if start >= then actual data is inserted (overrides) from start for the
 * length of actual data.
 * if start == -1 then actual data is appended to the end of the databuf
 *
 * @return databuf containing actual_data
 */
block* modify_data(uint32_t start, uint32_t length, byte* data_buf, byte* actual_data)
{

	int j = 0;
	int k = 0;
	byte * temp = NULL;
	block* data_blocks = NULL;

	if(start > 0)
	{
		for(int i = start; i < length+start; i++)
		{
			memcpy(data_buf[i], actual_data[j], BLKSIZE);
			j++;
		}
		temp = data_buf;
	}
	else if(start ==-1)
	{
		while(data_buf[j] != NULL)
		{
			j++;
		}
		//does adding 1 to the end make it null terminated
		j += length;
		temp = (byte*) calloc(j+1, sizeof(byte));
		for(int i = 0; i < j; i++)
		{
			if(i < j)
			{
				memcpy(temp, data_buf, BLKSIZE);
			}
			else
			{
				memcpy(temp, actual_data, BLKSIZE);
			}
		}
	}

	/**
	 * Divide up the byte arrays into block arrays
	 *
	for(int i = 0; i < j; i++)
	{
		data_blocks[k][i] = temp[i];
		if(i%BLKSIZE == 0 && i > 0)
		{
			k++;
		}
	}

	return data_blocks;
*/
	return NULL;
}

// TODO THIS HAS A MEMORY ISSUE, FIX GARBAGE DATA WITH DATA[40,41,42] FOR SOME REASON
block* segment_data_len(byte* data_buf, uint32_t length)
{
	uint32_t i = 0;
	uint32_t blocks = ceil(length / BLKSIZE);
	byte empty_block[BLKSIZE] = { NULL };

	/* The offset in the data buffer to copy the data into the block */
	uint32_t offset = 0;
	block* data_blocks = NULL;

	/* Copy each block into a 2D array containin the blocks */
	for (i = 0; i < blocks; ++i)
	{
		/* Increase the size of the data blocks array for one more block */
		data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(block));

		/* Copy the data_buf at the next offset into the array of data blocks */
		//data_blocks[i] = (byte*) calloc(BLKSIZE, sizeof(byte));
		/* Set the realloc'd memory to NULL before copying the data from the buffer */
		memcpy(data_blocks[i], empty_block, BLKSIZE);
		memcpy(data_blocks[i], data_buf + offset, BLKSIZE);
		offset += BLKSIZE;
	}

	/* Increase the data_blocks array for a final NULL termination block */
	data_blocks = (block*) realloc(data_blocks, (i + 1) * sizeof(byte*));
	memcpy(data_blocks[i], empty_block, BLKSIZE);

	return data_blocks;
}


/** sfs_write
 * Write the length bytes of data specified from a memory location to the
 * specified file. The parameter start gives the offset of the first byte in
 * the file that should be copied to. Alternatively, the value of start may be
 * set to -1, this indicates that the specified number of bytes should be
 * appended to the file. Appending (setting start to -1) is the only allowable
 * way to increase the length of a file.
 *
 * @param fd A file descriptor for the file to write data to
 * @param start The offset of the first byte in the file that should be written
 * to, if start is -1 then the data will be appended to the file
 * @param length The length of bytes of data to be written to the file
 * @param mem_pointer The memory location containing the bytes to write to file
 *
 * @return an integer value,
 * If the value > 0 the file write was a success
 * If the value <= 0 the file write was unsuccessful
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 *
 * @exception INSUFFICIENT_DISK_SPACE If the length of the blocks to be written
 * is greater than the amount of available blocks on disk
 */
int sfs_write(int fd, int start, int length, byte *mem_pointer)
{
	//TODO test write
	//TODO create encryption
	//TODO create decryption
	uint32_t blocks_needed = 0;
	inode inode_write = get_null_inode();
	uint32_t* new_inode_loc = NULL;
	uint32_t* data_block_locations = NULL;
	byte* temp = NULL;
	byte* data_buf = NULL;
	data_index data_location = {
			.index_location = NULL,
			.data_locations = NULL};
	block* data_block = NULL;
	int i = 0;

	if(fd >= 0 && length > 0 && start >= -1)
	{
		/**
		 * Validate the file descriptor on the system-wide-open file table
		 *  - If the file descriptor is not found return error
		 */
		if (validate_fd(fd) < 0)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}

		/** Based off a night of sleep and the codes
		 *
		 * blocks_needed = 1 //FOR INODE
		 * data_blocks = iterate_index(inode.location)
		 * data_buf = read_in_data(data_blocks)
		 *
		 * if start > 0
		 * 	if start + length > length of data_blocks in bytes
		 * 		return invalid write past file size
		 * 	data_buf = data_buf{until_start} conact mem_pointer conact data_buf
		 * 	after start + length}
		 * if start == -1
		 * 	data_buf = data_buf{all} concat mem_pointer
		 *
		 * divide into blocks(data_buf)
		 * data += get number of data blocks
		 * if(calc_num_free_blocks(data + num_of_index_blocks(data-1))) == NULL) //1 for the inode
		 * 	return 0;
		 * inode_location = get_free_block();
		 * data_blocks data_location = generate_index(d)
		 *
		 * int i = 0;
		 * while(data_location[i] != NULL)
		 * 	write_block(data_location.data_blocks[i], databuf[i])
		 * 	i++;
		 * populate_inode (data_location.index_block)
		 * journal link parent's index to inode
		 */
		blocks_needed++; //Inode block space
		inode_write = get_swoft_inode(fd);
		data_block_locations = iterate_index(inode_write.location, data_block_locations);

		data_buf = get_data(data_block_locations);

		blocks_needed += get_num_datablocks(data_buf);

		if(start >= 0)
		{
			if((start + length) >= i)
			{
				/**
				 * Invalid override
				 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
				 */
				return -1;
			}
			/**
			 * No new data blocks will be needed
			 */

		}
		else if(start == -1)
		{
			/**
			 * Add # of new blocks to blocks_needed
			 */
			blocks_needed += (int)ceil((start+length)/BLKSIZE);
		}

		/**
		 * Add the data to the data_buf
		 * Break it back into blocks
		 */
		data_block = modify_data(start, length, data_buf, mem_pointer);

		/**
		 * Check if the new write will fit onto the hard disk
		 */
		if((calc_num_free_blocks(blocks_needed + calc_index_blocks(blocks_needed-1))) == NULL) //1 for the inode
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}

		/**
		 * Create the new free block
		 */
		new_inode_loc = get_free_block();

		/**
		 * TODO Update file size
		 */

		/**
		 * Generate the new list of indexes
		 */
		data_location = generate_index(blocks_needed-1);

		i = 0;

		/**
		 * Write the data
		 * Check if the file needs to be encrypted
		 * 	- If it needs to be encrypted, encrypt the file
		 * Store the file into the block(s)
		 */
		while(data_location.data_locations[i] != NULL)
		{
			write_block(data_location.data_locations[i], data_block[i]);
			i++;
		}

		inode_write.location = data_location.index_location;

		/**
		 * journal link parent's index to inode
		 */

		/**
		 * return value > 0 if write was successful
		 * return value <= 0 then the write was a fail
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	}
	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return 0;
}


