#include "glob_data.h"
#include "traverse_tree.h"
#include "super_block.h"

uint32_t* traverse_file_system(char** tokens, bool create)
{
	int root_dir;
	locations inode_location = (uint32_t *) calloc(2, sizeof(uint32_t));
	locations index_block = NULL;
	int index;
	int second_last = 0;
	int i = 1;

	/**
	 * Retrieve the Superblock.
	 * 	- Retrieve the root's Inode location
	 */
	root_dir = get_root();

	/**
	 * Get the root's index block location
	 */
	index = get_index_block(root_dir);

	/**
	 * Retrieve list of contents in the root directory
	 * Iterate through the contents of the root directory and locate the
	 * directory or file that is found at the first index of the path parsed.
	 */
	index_block = iterate_index(index, NULL);
	if(index_block == NULL)
	{
		/**
		 * Failed to iterate root directory
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return NULL;
	}

	/*
	 * IF index_block[0] == NULL, aka no children yet
	 *
	 */
	if(index_block[0] == NULL)
	{
		if(tokens[0] != NULL)
		{
			if(create == false)
			{
				/**
				 * Invalid directory
				 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
				 */
				return NULL;
			}
		}
		else
		{
			inode_location[0] = root_dir;
			inode_location[1] = 0;
			return inode_location;
		}
	}

	/**
	 * Create a function that will go through the locations from the index block
	 * and check if a given file/directory is contained
	 */

	//tokens[0] cannot be null unless something messed up, since you cannot open
	//up a file with a path that only contains '/'
	inode_location[0] = find_inode(index_block, tokens[0]);

	if(inode_location[0] == 0 && create == true || tokens[1] == NULL && create == true)
	{
		inode_location[1] = 0;
		inode_location[0] = root_dir;

		/**
		 * Inode is root
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return inode_location;
	}

	if(create == true)
	{
		inode parent = *get_inode(inode_location[0]);
		if(parent.type == 0)
		{
			/**
			 * Invalid Path, cannot use file as a directory
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return NULL;
		}
		second_last = 1;
	}



	/**
	 * General structure of the traversal:
	 * 	- From Inode get index block location
	 * 	- From index block get locations
	 * 	- Compare locations with pathname's next entry
	 * 	Loop again...
	 * Errors thrown are:
	 * 	- File not found
	 * 	- Invalid pathway (directory not found)
	 */
	while(tokens[i+second_last] != NULL)
	{
		index_block = 0;

		/**
		 * get the list of locations from the index block
		 */

		index = get_index_block(inode_location[0]);

		/**
		 * index block is empty
		 */
		index_block = iterate_index(index, NULL);

		if(index_block == NULL)
		{
			/**
			 * No Children found
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return NULL;
		}

		/**
		 * Find the inode with the given name, the current token
		 */
		inode_location[0] = find_inode(index_block, tokens[i]);

		/**
		 * Inode not found, aka file/directory not found
		 */
		if (inode_location[0] == NULL)
		{
			/**
			 * Child not found
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return NULL;
		}
		i++;
	}
	inode_location[1] = i;

	/**
	 * Success
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return inode_location;
}
