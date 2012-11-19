#include "blockio.h"
#include "I_node.h"
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
	//TODO test gettype
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
	 * Retrieve the file type from the Inode
	 * return the file type from the Inode
	 */

	return get_type(inode_location);
}
