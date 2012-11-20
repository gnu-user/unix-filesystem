#include "blockio.h"
#include "index_block.h"
#include "system_open_file_table.h"

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
int sfs_read(int fd, int start, int length, char *mem_pointer)
{
	//TODO create read
	//TODO create encryption
	//TODO create decryption
	inode file_inode = get_null_inode();
	uint32_t index_block = 0;
	locations data_blocks = NULL;

	if(fd >= 0 && start > 0 && start < BLKSIZE && length > 0 &&
			start+length < BLKSIZE)
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
		 * Use the offset to find the start of where to read in the block
		 * Read the specified bytes of the given length into the buffer
		 */

		/**
		 * Get Inode
		 * 	- check that it is a file
		 */
		file_inode = get_swoft_inode(fd);

		/**
		 * Decrypt here if needed
		 */

		/**
		 * Get index block
		 */
		index_block = file_inode.location;

		if (iterate_index(index_block, data_blocks) == NULL)
		{
			return 0;
		}


		/**
		 * Search for offset point in data blocks
		 *  Given:
		 *  - 128 bytes per block, 31 blocks per index block
		 */

		/**
		 * Read for the required length
		 *  Given:
		 *  - 128 bytes per block, 31 blocks per index
		 *  (since multiple blocks could be desired)
		 *
		 *  Stored in mem_pointer
		 */

		/**
		 * return value > 0 if the file was read successfully
		 * return value <= 0 if the file was read unsuccessfully
		 */

		return 1;
	}
	return 0;
}
