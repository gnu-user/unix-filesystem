#include "blockio.h"
#include "traverse_tree.h"

/** sfs_delete
 * Delete a file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return an integer value,
 * If the value > 0 then the file was deleted successfully.
 * If the value <= 0 then the file failed to be delete.
 *
 * @exception FILE_NOT_FOUND If the file at the specified path does
 * not already exist
 */
int sfs_delete(char *pathname)
{
	//TODO create delete_file

	uint32_t inode_location = NULL;

	/**
	 * Traverse the file system to find the desired inode
	 * get the inode above the one you desired
	 */
	inode_location = traverse_file_system(pathname, true);

	if(inode_location == 0)
	{
		return -1;
	}

	/**
	 * Check if it is a directory
	 * 	- If so:
	 * 		Check if the directory is empty
	 * 			- If so:
	 * 				Error, user can only delete directories that are empty
	 */

	/**
	 * Update the status of the Inode, index block (and data blocks) in the free
	 * block list blocks.
	 *
	 * These blocks will need to be deleted the order of:
	 * data blocks (if file)
	 * index block
	 * Inode
	 *
	 * Since the data block locations are stored in the index block and the
	 * index block's location is stored in the Inode
	 */

	/**
	 * return value > 0 then the file was deleted successfully.
	 * return value <= 0 then the file failed to be delete.
	 */
	return 1;
}
