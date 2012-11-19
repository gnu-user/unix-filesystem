#include "blockio.h"
#include "I_node.h"
#include "index_block.h"
#include "super_block.h"
#include "system_open_file_table.h"

/** sfs_open
 * Opens the file specified by the pathname, if the file is successfully opened
 * a file descriptor is returned.
 *
 * @param pathname The full pathname of a file
 *
 * @return A file descriptor for the file opened
 * If the fd >= 0 then the file has successfully opened.
 * If the fd < 0 then the file has failed to open.
 *
 * @exception FILE_NOT_FOUND If the file specified in pathname does not exist
 */
int sfs_open(char *pathname)
{
	//TODO create open
	int root_dir;
	uint32_t inode_location = 0;
	locations index_block = NULL;
	int index;

	/**
	 * Parse pathname
	 */
	char** tokens = NULL;
	if(tokenize_path(pathname, tokens) == NULL)
	{
		return -1;
	}

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
		return -1;
	}
	/**
	 * Create a function that will go through the locations from the index block
	 * and check if a given file/directory is contained
	 */
	//inode_location = find_inode(index_block, pathname.nextElement);

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

	/*while(pathname.hasNext() && pathname.next + 1 != NULL)
	{
		index_block = NULL;
		index = get_index_block(inode_location);

		if(iterate_index(index, index_block) == NULL){
			return -1;
		}
		//inode_location = find_inode(index_block, pathname.nextElement);
		if (inode_location == NULL)
		{
			return -1;
		}
	}*/


	/**
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */

	return add_to_swoft(inode_location);
}

/**
 * The all of the information stored in the given file descriptor's Inode.
 *
 * @param fd integer, the file descriptor.
 *
 * @return an integer value,
 * if the value > 0 then the function is successful
 * if the value <= 0 then the function is unsuccessful
 */
int show_information(fd)
{
	if(fd >= 0)
	{
		/**
		 * Get the Inode from the swoft given the fd
		 */
		inode node;

		printf("Name: %s", node.name);
		if(node.type == true)
		{
			printf("Type: directory");
		}
		else
		{
			printf("Type: directory");
		}
		char read = '-';
		char write = '-';
		char execute= '-';
		if(node.read == true)
		{
			read = 'R';
		}
		if(node.write == true)
		{
			write = 'W';
		}
		if(node.execute == true)
		{
			execute ='X';
		}

		printf("Privileges: %c%c%c", read, write, execute);

		printf("Date created: %d", node.date_of_create);

		printf("Date last accessed: %d", node.date_last_accessed);

		printf("Date last modified: %d", node.date_last_modified);

		printf("File owner: %d", node.file_owner);

		printf("Last user modified: %d", node.last_user_modified);

		printf("File size: %d", node.file_size);

		printf("Index Block Location: %d", node.location);

		if(node.encrypted == true)
		{
			printf("Encrypted: True");
		}
		else
		{
			printf("Encrypted: False");
		}

		printf("Check sum: %d", node.check_sum);


		return 1;
	}
	return 0;
}
