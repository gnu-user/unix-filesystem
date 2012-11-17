#include "blockio.h"

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

	if(fd >= 0 && start > 0 && start < BLKSIZE && length > 0 &&
			start+length < BLKSIZE)
	{
		/**
		 * Validate the file descriptor on the system-wide-open file table
		 *  - If the file descriptor is not found return error
		 * Use the offset to find the start of where to read in the block
		 * Read the specified bytes of the given length into the buffer
		 *
		 * return value > 0 if the file was read successfully
		 * return value <= 0 if the file was read unsuccessfully
		 */

		return 1;
	}
	return 0;
}
