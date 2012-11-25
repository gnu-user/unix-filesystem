#include "glob_data.h"
#include "blockio.h"
#include "traverse_tree.h"
#include "get_size.h"

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
	//TODO test getsize
	int type = -1;
	int i = 1;
	uint32_t index_block = 0;
	locations inode_location = NULL;
	locations index_locations = NULL;
	char** tokens = NULL;
	int size = 0;

	/**
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		/**
		 * Invalid pathname
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

	/**
	 * Traverse the file system to find the desired inode
	 */
	inode_location = traverse_file_system(tokens, false);

	if(inode_location == NULL)
	{
		/**
		 * Invalid path or file/directory not found
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

	/**
	 * Check if it is a file or directory
	 * 	- If directory:
	 * 		Count entries
	 * 	- If file:
	 * 		get size
	 */
	type = get_type(inode_location[0]);

	index_locations = index_block_locations(inode_location[0], NULL);

	if(index_locations == NULL)
	{
		/**
		 * Invalid invalid index block
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return -1;
	}

	/**
	 * Count the number of index blocks
	 */
	while(index_locations[i+1] != NULL)
	{
		i++;
	}

	/**
	 * Add the inode
	 */
	i+=1;

	/**
	 * print out the number of index blocks + the inode block
	 */
	printf("Overhead Size =  %d\n", i*BLKSIZE);

	if(type == 0)
	{
		/**
		 * Get the size of the file from the Inode
		 * return the size of the file
		 */
		size =  get_size(inode_location[0]);
		printf("Size = %d\n", size);
		return size;
	}
	else if(type == 1)
	{
		/**
		 * Get the index block's location
		 */
		index_block = get_index_block(inode_location[0]);

		/**
		 * Return the number of locations found in the index block(s)
		 */
		size = count_files_in_dir(index_block);
		printf("Size = %d\n", size);
		return size;
	}
	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return -1;
}
