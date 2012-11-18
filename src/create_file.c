#include "blockio.h"
#include "super_block.h"
#include "I_node.h"

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
	int root_dir;
	/**
	 * Check for valid type = 0 or = 1
	 */
	if(type == 0 || type == 1)
	{
		/**
		 * Check if there is enough space to allocate for the new file/directory
		 */

		/**
		 * Parse pathname
		 */
		//parse_path(pathname);

		/**
		 * Retrieve the root direct's location
		 *  - Retrieve the root's Inode location
		 */
		root_dir = get_root();

		/**
		 * Get the root's index block location
		 */
		int root_index = get_index_block(root_dir);

		/**
		 * Iterate through the rest of the directories (until the lowest
		 * directory is found)
		 */

		/**
		 * Check if the there is another file with the given name
		 * 	- If there is another file, there is an invalid file name error
		 */

		inode new_block;
		//new_block->name = last_element_in_pathname;
		if(type == 0){
			new_block.type = false;
		}
		else{
			new_block.type = true;
		}

		/**
		 * Create index block
		 */

		/**
		 * Create data block (IF file block)
		 */

		/**
		 * Allocate blocks
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
