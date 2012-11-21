#include "block_func.h"

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
int sfs_write(int fd, int start, int length, char *mem_pointer)
{
	//TODO create write
	//TODO create encryption
	//TODO create decryption

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
		 * Check the encryption property
		 * 	- If encrypted it will be decrypted
		 */

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
		 * concat the mem_pointer to the blocks before it (and after)
		 *
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

/**
 * if start >= then actual data is inserted (overrides) from start for the
 * length of actual data.
 * if start == -1 then actual data is appended to the end of the databuf
 *
 * @return databuf containing actual_dat
 */
uint32_t* modify_data(uint32_t start, uint32_t* databuf, uint32_t* actual_data)
{
	return 0;
}

uint32_t* getData(uint32_t* location)
{
	int i = 0;
	uint32_t* databuf = NULL;
	byte* buf = NULL;
	int retval = 0;

	while(location[i] != NULL)
	{
		buf = allocate_buf(buf, BLKSIZE);

		retval = read_block(location[i], buf);
		if(retval != 0)
		{
			return NULL;
		}
		concat(databuf, buf);
		i++;
	}
	return databuf;
}
