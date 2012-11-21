#include "blockio.h"
#include "super_block.h"
#include "traverse_tree.h"
#include "string.h"
#include <time.h>

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
	inode new_block = get_null_inode();
	char** tokens;
	uint32_t* inode_location = NULL;
	locations index_block = NULL;
	uint32_t index_location = NULL;
	uint32_t data_location = NULL;
	uint32_t new_inode_location[3] = {NULL, NULL, NULL};
	byte* buf = NULL;
	int retval = 0;

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

		/**
		 * Invalid path or path does not exist
		 */
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
		 * Check File/directory already exists
		 */
		if(find_inode(index_block, tokens[inode_location[1]]) != NULL)
		{
			return 0;
		}

		/**
		 * Check if there is enough space on the disk for the new create
		 * (2 blocks for directory or file)
		 */
		if(calc_num_free_blocks(2) == NULL)
		{
			/**
			 * Not enough space
			 */
			return -1;
		}

		/**
		 * Get a free block location for the Inode
		 */
		new_inode_location[0] = get_free_block();

		strcpy(new_block.name, tokens[inode_location[1]]);

		if(type == 0){
			new_block.type = false;
			new_block.file_size = 2 * BLKSIZE;
		}
		else
		{
			new_block.type = true;
			/**
			 * Identify whether the file is encrypted
			 */
			new_block.encrypted = 0;
			new_block.file_size = 2 * BLKSIZE;
		}

		/**
		 * Create an index block empty index block
		 */
		index_location = generate_index(0);

		if (index_location == NULL)
		{
			/**
			 * de-allocate the inode
			 * TODO make sure that the new_inode_location is null terminated
			 */

			if(update_fbl(NULL, new_inode_location) == NULL)
			{
				return -1;
			}
			return 0;
		}

		/**
		 * Fill in the information to be stored in the Inode
		 */
		//date_of_create = cur_date;
		//date_last_accessed = cur_date;
		//date_last_modified = cur_date;
		//file_owner = cur_user;
		//last_user_modified = cur_user;

		/**
		 * Assign locations
		 * 	- Store the index block's location in the Inode block
		 * 	- Store the data block's location in the index block
		 */
		new_block.location = index_location;

		/**
		 * Store the blocks on disk
		 * 	- If there is an error while writing, de-allocate the blocks
		 * 	  return error
		 */
		buf = allocate_buf(buf, BLKSIZE);

		buf = (byte *) copy_to_buf((byte *)&new_block, (byte *)buf, sizeof(new_block), BLKSIZE);
		retval = put_block(new_inode_location[0], buf);

		if(retval != 0)
		{
			/**
			 * De-allocate the index blocks
			 */
			new_inode_location[1] = index_location;
			if(update_fbl(NULL, new_inode_location) == NULL)
			{
				return -1;
			}
			return 0;
		}

		/**
		 * Add the inode's location to the parent's index list
		 * If add location fails de-allocate Inode and index block
		 * TODO check for success addition to parent index block
		 */
		if(link_inode(inode_location[0], new_inode_location) < 0)
		{
			new_inode_location[1] = index_location;
			if(update_fbl(NULL, new_inode_location) == NULL)
			{
				return -1;
			}
			return 0;
		}

		/**
		 * return value > 0 the file create was a success
		 * return value <= 0 the file create was unsuccessful
		 */
		return 1;
	}
	return 0;
}
