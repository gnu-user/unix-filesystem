#include "blockio.h"
#include "I_node.h"
#include "traverse_tree.h"

/** sfs_getsize
 * Get the size (in blocks) of the file with the pathname specified.
 *
 * @param pathname The pathname of the file or directory, must be full directory
 * path
 * If it is a file then the size of the file will be returned
 * If it is a directory the number of entries will be returned
 *
 * @return the size of the given file
 * If the value < 0 then an error has occurred.
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_getsize(char *pathname)
{
	//TODO finish getsize
	//TODO test getsize
	int type = -1;
	uint32_t index_block = NULL;
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
	 * Check if it is a file or directory
	 * 	- If directory:
	 * 		Count entries
	 * 	- If file:
	 * 		get size
	 */
	type = get_type(inode_location);
	if(type == 0)
	{
		/**
		 * Get the size of the file from the Inode
		 * return the size of the file
		 */
		return get_size(inode_location);
	}
	else if(type == 1)
	{
		/**
		 * Get the index block's location
		 */
		index_block = get_index_block(inode_location);

		/**
		 * Return the number of locations found in the index block(s)
		 */
		return count_locations(index_block);
	}
	return -1;
}
