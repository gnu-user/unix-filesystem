#include "blockio.h"
#include "I_node.h"
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

	/**
	 * Parse pathname
	 */
	//parse_path(pathname);

	/**
	 * Retrieve the Superblock.
	 * 	- Retrieve the root's Inode location
	 */
	root_dir = get_root();

	/**
	 * Get the root's index block location
	 */
	int root_index = get_index_block(root_dir);

	/**
	 * Retrieve list of contents in the root directory
	 * Iterate through the contents of the root directory and locate the
	 * directory or file that is found at the first index of the path parsed.
	 */

	/**
	 * Iterate through the rest of the directories (until the file desired is
	 * found)
	 * Errors thrown are:
	 * 	- File not found
	 * 	- Invalid pathway (directory not found)
	 */

	/**
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */

	//Given the Inode has been found:

	//int file_inode = 0;

	//return add_to_swoft(file_inode);

	return 0;
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
