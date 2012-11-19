#include "blockio.h"
#include "super_block.h"
#include "I_node.h"
#include "traverse_tree.h"

/** sfs_create
 * Create a file with the pathname specified if there is not already a file with
 * the same pathname, the pathname must contain the full directory path. The
 * parameter type specifies whether a regular file or a directory file should be
 * created.
 *
 * @param pathname The pathname of file to create, must be full directory path
 * @param type The type of file to create, zero for a regular file, one for a
 * directory file
 *
 * @return a integer value
 * If the value > 0 the file create was a success
 * If the value <= 0 the file create was unsuccessful
 *
 * @exception FILE_EXISTS If the specified file name is already in use
 * @exception INVALID_FILE_TYPE If the file type specified is not a regular file
 * (0) or a directory file (1)
 * @exception INVALID_PATH If the pathname (except the last) does not already exist
 * @exception INSUFFICIENT_DISK_SPACE If the length of the blocks to be written
 * is greater than the amount of available blocks on disk
 */
int sfs_create(char *pathname, int type)
{
	//TODO create create_file
	inode new_block = NULL;
	char** tokens;
	uint32_t* inode_location = NULL;
	locations index_block = NULL;

	/**
	 * Check for valid type = 0 or = 1
	 */
	if(type == 0 || type == 1)
	{
		/**
		 * Parse the pathname
		 */
		tokens = tokenize_path(pathname);
		if(tokens == NULL)
		{
			return 0;
		}

		/**
		 * Traverse the file system to find the directory containing the desired
		 * inode
		 */
		inode_location = traverse_file_system(tokens, true);

		if(inode_location == NULL)
		{
			return 0;
		}
		/**
		 * inode_location[0] = the location of the directory's inode,
		 * inode_location[1] = the token index for the last element
		 */

		/**
		 * Check if the there is another file with the given name
		 * 	- If there is another file, there is an invalid file name error
		 */
		if(iterate_index(inode_location[0], index_block) == NULL){
			return 0;
		}

		/**
		 * File/directory already exists
		 */
		if(find_inode(index_block, tokens[inode_location[1]]) != NULL)
		{
			return 0;
		}


		new_block->name = tokens[inode_location[1]];
		if(type == 0){
			new_block.type = false;
		}
		else{
			new_block.type = true;
		}

		/**
		 * Create index block
		 */
		//create/generate index block

		/**
		 * Create data block (IF file block)
		 */

		/**
		 * Allocate blocks
		 * Set as being used on the free block list
		 */

		/**
		 * Assign locations
		 * 	- Store the index block's location in the Inode block
		 * 	- Store the data block's location in the index block
		 */

		/**
		 * Store the blocks onto the disk at the assigned locations.
		 */

		/**
		 * return value > 0 the file create was a success
		 * return value <= 0 the file create was unsuccessful
		 */
		return 1;
	}
	return 0;
}
