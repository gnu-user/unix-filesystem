#include "glob_data.h"
#include "block_func.h"
#include "index_block.h"
#include "system_open_file_table.h"
#include <math.h>

/** sfs_read
 * Copy the length of bytes of data specified from a regular file to memory
 * location specified by mem_pointer. The parameter start gives the offset
 * of the first byte in the file that should be copied.
 *
 * @param fd A file descriptor for the file to read data from
 * @param start The offset of the first byte in the file that should be copied
 * @param length The length of bytes of data to copy from the file
 * @param mem_pointer The memory location to store the data read from the file
 *
 * @return an integer value,
 * if the value > 0 then the file was read successfully
 * if the value <= 0 then the file was read unsuccessfully
 *
 * @exception FILE_LENGTH_OVERRUN If the file cannot be read correctly because
 * the length of bytes specified exceeds the length of the file, no data will be
 * copied from the file if an overrun occurs.
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 */
int sfs_read(int fd, int start, int length, byte *mem_pointer)
{
	//TODO test read
	//TODO create encryption
	//TODO create decryption

	inode file_inode = get_null_inode();
	uint32_t index_block = 0;
	locations data_blocks = NULL;
	byte* data_buf = NULL;
	uint32_t start_block = NULL;
	uint32_t i;
	byte* temp = NULL;
	mem_pointer = NULL;

	if(fd >= 0 && fd < NUMOFL && start >= -1 && length > 0)
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

		/**
		 * Check the journal for entries (if needs to flush)
		 */

		/**
		 * Use the offset to find the start of where to read in the block
		 * Read the specified bytes of the given length into the buffer
		 */

		/**
		 * Get Inode
		 * 	- check that it is a file
		 */
		file_inode = get_swoft_inode(fd);

		/**
		 * Get index block
		 */
		index_block = file_inode.location;

		data_blocks = iterate_index(index_block, NULL);

		if (data_blocks == NULL)
		{
			/**
			 * File is empty
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}

		data_buf = get_data(data_blocks);

		/**
		 * Since start is offset (number of bytes offset)
		 * ceil(start/BLKSIZE)
		 */

		/**
		 * Count the number of data blocks
		 */
		int count = 0;
		while(data_blocks[count] != NULL)
		{
			/**
			 * Calculate the size of the data blocks in bytes
			 */
			count++;
		}

		if(start+length > count*BLKSIZE)
		{
			/**
			 * Read pass end of file
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}

		/**
		 * copy the data block at start into memory
		 * TODO figure out how to fix missing reference for ceil
		 */
		start_block = (uint32_t)(ceil((double)(start)/BLKSIZE));

		/**
		 * data_buf = data_blocks parsed
		 * Search through data_buf for byte start where start >= 0
		 * if start+length > length(data_buf)
		 * 	return invalid read past end of file.
		 * mem_pointer = copy data_buf from start to index = start + length
		 */
		i = 0;
		while(data_blocks[i+start] != NULL && i < length)
		{
			/**
			 * concat the mem_pointer
			 */
			temp = (byte*) concat_len(mem_pointer, data_blocks[start_block+i], sizeof(byte), BLKSIZE);
			free(mem_pointer);
			mem_pointer = temp;
			i++;
		}

		/**
		 * Update last_accessed
		 */

		/**
		 * return value > 0 if the file was read successfully
		 * return value <= 0 if the file was read unsuccessfully
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	}

	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return 0;
}
