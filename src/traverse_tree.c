#include "glob_data.h"
#include "traverse_tree.h"
#include "super_block.h"

uint32_t* traverse_file_system(char** tokens, bool create)
{
	int root_dir;
	uint32_t inode_location[2] = {NULL, NULL};
	locations index_block;
	int index;
	int second_last = 0;
	int i = 0;

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

	if(iterate_index(index, index_block) == NULL){
		return NULL;
	}

	/**
	 * Create a function that will go through the locations from the index block
	 * and check if a given file/directory is contained
	 */

	//tokens[0] cannot be null unless something messed up, since you cannot open
	//up a file with a path that only contains '/'
	inode_location[0] = find_inode(index_block, tokens[0]);

	if(create == true)
	{
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
	while(tokens[i+1+second_last] != NULL)
	{
		index_block = 0;

		/**
		 * get the list of locations from the index block
		 */
		index = get_index_block(inode_location[0]);


		/**
		 * index block is empty
		 */
		if(iterate_index(index, index_block) == NULL){
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
			return NULL;
		}
		i++;
	}
	inode_location[1] = i+1;
	return inode_location;
}
