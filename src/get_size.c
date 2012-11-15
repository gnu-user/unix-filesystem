#include "blockio.h"

/** sfs_getsize
 * Get the size (in blocks) of the file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return the size of the given file
 * Ff the value < 0 then an error has occurred.
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_getsize(char *pathname)
{
	//TODO create get_size

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
	 * Get the size of the file from the Inode
	 * return the size of the file
	 */
	return 0;
}
