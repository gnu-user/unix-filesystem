#include "glob_data.h"
#include "block_func.h"
#include "I_node.h"
#include "system_open_file_table.h"
#include "index_block.h"
#include <math.h>

/**
 * if start >= then actual data is inserted (overrides) from start for the
 * length of actual data.
 * if start == -1 then actual data is appended to the end of the databuf
 *
 * @return databuf containing actual_dat
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
	 */
	for(int i = 0; i < j; i++)
	{
		data_blocks[k][i] = temp[i];
		if(i%BLKSIZE == 0 && i > 0)
		{
			k++;
		}
	}

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
	//TODO create write
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
			return 0;
		}

		/**
		 * Check if start+length-1 > file_size-(Inode(1) + index_block(n))
		 * 	- return error if so
		 */

		/**
		 * Check if the new write will fit onto the hard disk
		 * 	- If the new write does not fit, through error
		 * 	- If there is enough space allocate the space from the free block list
		 *
		 * 	Enough space involves re-writing the entire file, and if the file is
		 * 	being appended it the given length /BLKSIZE
		 */

		/* Based off the codes
		read_block inode (data++)
		iterate index //now we have all data locations (Ibuf)
		date+= length(databuf)
		databuf[] = getData(IBuf)
		modifydate(start, databuf, acutaldata)
		if(calc_num_free_blocks(data + num_of_index_blocks(length(databuf))) == NULL)
		{
			return 0;
		}
		inode_location = get_free_block;
		data_location = generate_index(length(databuf));

		populate inode in Inode buf(index_location)
		Update date modified, date accessed, and last user to access
		write_block(inode_location, inode_buf)
		journal link inode
		*/

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
		i = 0;
		while(data_buf[i] != NULL)
		{
			i++;
		}
		blocks_needed += (int)ceil(i/BLKSIZE);

		if(start >= 0)
		{
			if((start + length) >= i)
			{
				/**
				 * Invalid override
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
		 */
		data_block = modify_data(start, length, data_buf, mem_pointer);

		/**
		 * Break it back into blocks
		 */

		if((calc_num_free_blocks(blocks_needed + calc_index_blocks(blocks_needed-1))) == NULL) //1 for the inode
		{
			return 0;
		}

		new_inode_loc = get_free_block();

		data_location = generate_index(blocks_needed-1);

		i = 0;
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
		 * Write the data
		 * Check if the file needs to be encrypted
		 * 	- If it needs to be encrypted, encrypt the file
		 * Store the file into the block(s)
		 */

		/**
		 * return value > 0 if write was successful
		 * return value <= 0 then the write was a fail
		 */
		return 1;
	}
	return 0;
}


