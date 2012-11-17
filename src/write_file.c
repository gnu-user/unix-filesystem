#include "blockio.h"

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

	/**
	 * Validate the file descriptor on the System open file table
	 * 	- Throw an error otherwise
	 * Check the encryption property
	 * 	- If encrypted it will be decrypted
	 * Check if the new write will fit onto the hard disk
	 * 	- If the new write does not fit, through error
	 * 	- If there is enough space allocate the space from the free block list
	 * Write the data
	 * Check if the file needs to be encrypted
	 * 	- If it needs to be encrypted, encrypt the file
	 * Store the file into the block(s)
	 *
	 * return value > 0 if write was successful
	 * return value <= 0 then the write was a fail
	 */

	return 1;
}
