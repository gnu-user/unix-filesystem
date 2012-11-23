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
	//TODO test close

	/**
	 * Check if a valid file descriptor is given
	 */
	if(fd >= 0)
	{

		/**
		 * Validate the file descriptor on the System open file table
		 * 	- Throw an error otherwise
		 */
		if (validate_fd(fd) < 0)
		{
			return 0;
		}

		/**
		 * 	Remove the file descriptor from the System open file table
		 */
		remove_fd(fd);

		/**
		 * 	return value > 0 the file close was a success
		 * 	return value <= 0 the file close was unsuccessful
		 */
		return 1;
	}
	return 0;
}
