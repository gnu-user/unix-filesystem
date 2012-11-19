#include "blockio.h"
#include "I_node.h"

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
	//TODO test getsize

	uint32_t inode_location = NULL;

	/**
	 * Traverse the file system to find the desired inode
	 */
	inode_location = traverse_file_system(pathname);

	if(inode_location == 0)
	{
		return -1;
	}

	/**
	 * Get the size of the file from the Inode
	 * return the size of the file
	 */

	return get_size(inode_location);
}
