#include "blockio.h"

/** sfs_gettype
 * Get the type of the file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return the file type of the given file
 * If the file type >= 0 then the file type retrieval is a success
 * 	If the file type is 0, or 1 then the file is known
 * 	If the file type > 1 then the file is not known
 * If the file type < 0 then the file type retrieval has failed
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_gettype(char *pathname)
{
	//TODO create gettype

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
	 * Retrieve the file type from the Inode
	 * return the file type from the Inode
	 */
	return 0;
}
