#include "blockio.h"

/** sfs_close
 * Closes the file, which indicates that the file is no longer needed
 *
 * @param fd A file descriptor for the file to close
 *
 * @return a integer value
 * If the value > 0 the file close was a success
 * If the value <= 0 the file close was unsuccessful
 */
int sfs_close(int fd)
{
	//TODO create close_file

	/**
	 * Validate the file descriptor on the System open file table
	 * 	- Throw an error otherwise
	 * 	Remove the file descriptor from the System open file table
	 *
	 * 	return value > 0 the file close was a success
	 * 	return value <= 0 the file close was unsuccessful
	 */
	return 1;
}
