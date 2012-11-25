#include "glob_data.h"
#include "blockio.h"
#include "traverse_tree.h"
#include "free_block_list.h"
#include "system_open_file_table.h"
#include "delete_file.h"

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
	//TODO test delete
	char** tokens;
	uint32_t* parent_location = NULL;
	locations index_block = {NULL};
	uint32_t* inode_loc = {NULL, NULL};
	int type = -1;

	/**
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		/**
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 0;
	}

	/**
	 * Traverse the file system to find the desired inode
	 * get the inode above the one you desired
	 */
	parent_location = traverse_file_system(tokens, true);

	if(parent_location == NULL)
	{
		/**
		 * Parent not found
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

	index_block = iterate_index(parent_location[0], NULL);
	if(index_block == NULL){
		/**
		 * Empty or no index block
		 *TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 0;
	}

	/**
	 * Find the inode of the file or directory with the given file name in the
	 * given index block list
	 */
	inode_loc[0] = find_inode(index_block, tokens[parent_location[1]]);

	if(inode_loc[0] == NULL)
	{
		/**
		 * Inode not found
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 0;
	}

	/**
	 * Check if it is a directory
	 * 	- If so:
	 * 		Check if the directory is empty
	 * 			- If so:
	 * 				Error, user can only delete directories that are empty
	 */
	type = get_type(inode_loc[0]);


	index_block = iterate_index(get_index_block(inode_loc[0]), NULL);
	if(index_block == NULL)
	{
		/**
		 * Invalid index block
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

	if (type == 1)
	{
		if(index_block[0] != NULL)
		{
			/**
			 * Directory has children
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}
	}
	else if(type == 0)
	{
		/**
		 * Delete the data blocks (each time update the free_block list)
		 */
		update_fbl(NULL, index_block);
	}

	/**
	 * Delete the index blocks (each time update the free_block list)
	 */
	update_fbl(NULL, index_block_locations(get_index_block(inode_loc[0]), NULL));

	/**
	 * Delete the Inode block (update the free_block list)
	 */
	update_fbl(NULL, inode_loc);

	/**
	 * Delete all swoft entries for the given file
	 *
	 * TODO change to use uuid to identify the file descriptor, not crc
	 */
	if(find_and_remove(get_name(inode_loc[0]), get_uuid(inode_loc[0])))
	{
		/**
		 * Failed to remove files from swoft
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -2;
	}

	/**
	 * get parents indicies, cause its a directory
	 * delete index onto it (concat)
	 * Ensure that the number of indexes in the index block is NOT empty at
	 * this point or else it is invalid
	 * rebuild index
	 */
	/**
	 * TODO journal linking the newly updated fbl
	 * TODO journal removing the index location from parent
	 * Delete the index location from the index block of the parent directory
	 */
	//remove_location(get_index_block(parent_location[0]));

	/**
	 * return value > 0 then the file was deleted successfully.
	 * return value <= 0 then the file failed to be delete.
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return 1;
}
