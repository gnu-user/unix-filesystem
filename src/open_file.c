#include "blockio.h"

/** sfs_open
 * Opens the file specified by the pathname, if the file is successfully opened
 * a file descriptor is returned.
 *
 * @param pathname The full pathname of a file
 *
 * @return A file descriptor for the file opened
 * If the fd >= 0 then the file has successfully opened.
 * If the fd < 0 then the file has failed to open.
 *
 * @exception FILE_NOT_FOUND If the file specified in pathname does not exist
 */
int sfs_open(char *pathname)
{
	//TODO create open

	/**
	 * Parse pathname
	 */
	//parse_path(pathname);

	/**
	 * Retrieve the Superblock.
	 * Retrieve the root director Inode
	 * Retrieve the root director's index block
	 * Use the path name to traverse the file structure
	 * 	- Repeatedly Retrieve director's Inode, then the index block to
	 * 	  retrieve the next directory and so on...
	 * 	- This progress is done until the path has been completed or the file
	 * 	  has been found.
	 * 	- The file can not be found
	 * 	- The path name could be invalid it could be either bad entry or
	 * 	  directory not found
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */

	return 0;
}
