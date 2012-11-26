#include "glob_data.h"
#include "super_block.h"
#include "traverse_tree.h"
#include "block_func.h"
#include "create_file.h"
#include <string.h>
#include <time.h>

#define CREATE_SIZE 2

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
	//TODO test create
	inode new_block = get_null_inode();
	char** tokens;
	locations inode_loc = NULL;
	locations index_block = NULL;
	data_index index_location = {0};
	uint32_t data_location = NULL;
	uint32_t new_inode_location[3] = {NULL, NULL, NULL};
	byte* buf = NULL;
	uint32_t i = 0;
	int parent_offset = 0;
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
			/**
			 * TODO validate this error code
			 */
			print_error(INVALID_PATH);
			return 0;
		}

		/**
		 * Traverse the file system to find the directory containing the desired
		 * inode
		 */

		if(tokens[0] != NULL)
		{
			inode_loc = traverse_file_system(tokens, true);

			/**
			 * Invalid path or path does not exist
			 */
			if(inode_loc == NULL)
			{
				/**
				 * TODO validate this error code
				 */
				print_error(INVALID_PATH);
				return 0;
			}

			/**
			 * inode_loc[0] = the location of the directory's inode,
			 * inode_loc[1] = the token index for the last element
			 */

			/**
			 * Check if the there is another file with the given name
			 * 	- If there is another file, there is an invalid file name error
			 */
			index_block = iterate_index(get_index_block(inode_loc[0]), NULL);

			if(index_block != NULL)
			{
				/**
				 * Check File/directory already exists
				 */
				if(find_inode(index_block, tokens[inode_loc[1]]) != NULL)
				{
					print_error(INVALID_FILE_NAME);
					return 0;
				}

				i = 0;
				while(index_block[i] != NULL)
				{
					i++;
				}

				if(i%(int)(floor(BLKSIZE/sizeof(uint32_t)) - 1) == 0)
				{
					parent_offset++;
				}
			}

			/**
			 * Check if there is enough space on the disk for the new create
			 * (2 blocks for directory or file)
			 */
		}
		else
		{
			//TODO make so if ROOT dir is already created it wont be created again.
			//If ROOT EXISTS  RETURN ERROR
			if(validate_root_dir == -1)
			{
				inode_loc = SUPER_BLOCK;
			}
			else
			{
				/**
				 * Cannot override root
				 * TODO validate this error code
				 */
				print_error(INVALID_PATH);
				return -1;
			}
		}

		if(calc_num_free_blocks(CREATE_SIZE + parent_offset) == NULL)
		{
			/**
			 * Not enough space
			 * TODO validate this error code
			 */
			print_error(INSUFFICIENT_DISK_SPACE);
			return -1;
		}

		/**
		 * Check if the name is 7 chars
		 */
		/*if(tokens[0] != NULL)
		{
			if(strlen(tokens[inode_loc[1]]) > 6)
			{
				/**
				 * Invalid path name component, File name to long
				 * TODO validate this error code
				 */
		/*
				print_error(INVALID_PATH_LENGTH);
				return -1;
			}
		}*/

		/**
		 * Get a free block location for the Inode
		 */
		new_inode_location[0] = get_free_block();

		if(new_inode_location[0] == 0)
		{
			/**
			 * TODO validate this error code
			 */
			print_error(INSUFFICIENT_DISK_SPACE);
			return 0;
		}

		/**
		 * Copy the name into the inode
		 */
		if(tokens[0] != NULL)
		{
			strcpy(new_block.name, tokens[inode_loc[1]]);
		}
		else{

			strncpy(new_block.name, "/", 1);
		}

		/**
		 * Initialize values depending on the file type
		 */
		if(type == 0){
			new_block.type = false;
		}
		else
		{
			new_block.type = true;
			/**
			 * Identify whether the file is encrypted
			 */
			new_block.encrypted = 0;

		}

		new_block.file_size = CREATE_SIZE * BLKSIZE;

		/**
		 * Fill in the information to be stored in the Inode
		 * TODO fill in times and user info
		 */
		//date_of_create = cur_date;
		//date_last_accessed = cur_date;
		//date_last_modified = cur_date;
		//file_owner = cur_user;
		//last_user_modified = cur_user;

		/**
		 * Generate CRC for inode for unique identifier
		 */

		/**
		 * Create an index block empty index block
		 */
		index_location = generate_index(0);

		if(index_location.index_location == NULL)
		{
			/**
			 * de-allocate the inode
			 * TODO make sure that the new_inode_location is null terminated
			 */

			if(update_fbl(NULL, new_inode_location) == NULL)
			{
				/**
				 * TODO validate this error code
				 */
				print_error(ERROR_UPDATING_FBL);
				return -1;
			}
			/**
			 * TODO validate this error code
			 */
			print_error(INDEX_ALLOCATION_ERROR);
			return 0;
		}

		/**
		 * Assign locations
		 * 	- Store the index block's location in the Inode block
		 * 	- Store the data block's location in the index block
		 */
		new_block.location = index_location.index_location;

		/**
		 * Store the blocks on disk
		 * 	- If there is an error while writing, de-allocate the blocks
		 * 	  return error
		 */

		buf = allocate_buf(buf, BLKSIZE);

		buf = (byte *) copy_to_buf((byte *) &new_block, (byte *)buf, sizeof(new_block), BLKSIZE);
		retval = write_block(new_inode_location[0], buf);


		if(retval != 0)
		{
			/**
			 * De-allocate the index blocks
			 */
			new_inode_location[1] = index_location.index_location;
			if(update_fbl(NULL, new_inode_location) == NULL)
			{
				/**
				 * TODO validate this error code
				 */
				print_error(ERROR_UPDATING_FBL);
				return -1;
			}
			/**
			 * TODO validate this error code
			 */
			print_error(DISK_WRITE_ERROR);
			return 0;
		}

		/**
		 * get parents indicies, cause its a directory
		 * add index onto it (concat)
		 * Ensure that the number of indexes in the index block is NOT empty at
		 * this point or else it is invalid
		 * rebuild index
		 */

		/**
		 * Add the inode's location to the parent's index list
		 * If add location fails de-allocate Inode and index block
		 *
		 * TODO check for success addition to parent index block
		 * TODO link the inode to the parent Inode
		 */
		if(tokens[0] != NULL)
		{
			if(link_inode_to_parent(inode_loc[0], new_inode_location[0]) < 0)
			{
				new_inode_location[1] = index_location.index_location;
				if(update_fbl(NULL, new_inode_location) == NULL)
				{
					//TODO validate this error code
					print_error(ERROR_UPDATING_FBL);
					return -1;
				}
				//TODO validate this error code
				print_error(ERROR_BLOCK_LINKAGE);
				return 0;
			}
		}
		free(buf);

		/**
		 * TODO updfree(buf);ate size of parent
		 */

		/**
		 * TODO update fbl as well
		 */

		/**
		 * return value > 0 the file create was a success
		 * return value <= 0 the file create was unsuccessful
		 * TODO validate this error code
		 */
		print_error(SUCCESS);
		return 1;
	}
	/**
	 * TODO validate this error code
	 */
	print_error(INVALID_FILE_TYPE);
	return 0;
}
