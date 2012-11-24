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
	if(fd >= 0 && fd < NUMOFL)
	{

		/**
		 * Validate the file descriptor on the System open file table
		 * 	- Throw an error otherwise
		 */
		if (validate_fd(fd) < 0)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}

		/**
		 * 	Remove the file descriptor from the System open file table
		 */
		remove_fd(fd);

		/**
		 * 	return value > 0 the file close was a success
		 * 	return value <= 0 the file close was unsuccessful
		 * 	TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	}
	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return 0;
}
