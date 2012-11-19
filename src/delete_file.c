#include "blockio.h"

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
	 */
	inode_location = traverse_file_system(pathname);

	if(inode_location == 0)
	{
		return -1;
	}

	/**
	 *** Note that deleting a block also means to update the free block list
	 *** with the new status of the block (aka free)
	 * Recursively delete all of the blocks assosicated to the index block.
	 * 	- this will account for both directories and files.
	 * Delete the index block
	 * Delete the Inode
	 * Delete the pointer in the containing directory's index block.
	 *
	 * return value > 0 then the file was deleted successfully.
	 * return value <= 0 then the file failed to be delete.
	 */
	return 1;
}
