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
	char** tokens;
	uint32_t* inode_location = NULL;
	locations index_block = NULL;
	uint32_t inode = NULL;
	int type = -1;

	/**
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		return 0;
	}

	/**
	 * Traverse the file system to find the desired inode
	 * get the inode above the one you desired
	 */
	inode_location = traverse_file_system(pathname, true);

	if(inode_location == NULL)
	{
		return -1;
	}

	if(iterate_index(inode_location[0], index_block) == NULL){
		return 0;
	}

	inode = find_inode(index_block, tokens[inode_location[1]]);

	if(inode == NULL)
	{
		return 0;
	}

	/**
	 * Check if it is a directory
	 * 	- If so:
	 * 		Check if the directory is empty
	 * 			- If so:
	 * 				Error, user can only delete directories that are empty
	 */
	type = get_type(inode);

	if(iterate_index(inode_location[0], index_block) == NULL || (type == 1 &&
			index_block != NULL))
	{
		return 0;
	}


	if(type == 0)
	{
		/**
		 * Delete the data blocks (each time update the free_block list)
		 */
		update_fbl(iterate_fbl(get_free_block_index()), NULL, index_block);
	}

	/**
	 * Delete the index blocks (each time update the free_block list)
	 */
	//update_fbl(iterate_fbl(get_free_block_index()), NULL, indexes);

	/**
	 * Delete the Inode block (update the free_block list)
	 */
	update_fbl(iterate_fbl(get_free_block_index()), NULL, inode);

	/**
	 * Delete the index location from the index block of the parent directory
	 */

	/**
	 * return value > 0 then the file was deleted successfully.
	 * return value <= 0 then the file failed to be delete.
	 */
	return 1;
}
