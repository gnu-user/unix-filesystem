#include "blockio.h"

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
	/**
	 * Check for valid type = 0 or = 1
	 * Check if there is enough space to allocate for the new file/directory
	 */

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
	 * Check if the there is another file with the given name
	 * 	- If there is another file, there is an invalid file name error
	 * Create
	 * 	- if type = 0 create the file's Inode block, index block, and data block
	 * 	- if type = 1 create the directory's Inode block, and index block
	 *
	 * return value > 0 the file create was a success
	 * return value <= 0 the file create was unsuccessful
	 */
	return 0;
}
