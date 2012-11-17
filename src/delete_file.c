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
	 * Retrieve the index block
	 *
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
