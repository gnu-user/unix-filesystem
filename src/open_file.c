#include "blockio.h"
#include "I_node.h"

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
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */

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

		printf("Name: %s", node->name);
		if(node->type == true)
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
		if(node->read == true)
		{
			read = 'R';
		}
		if(node->write == true)
		{
			write = 'W';
		}
		if(node->execute == true)
		{
			execute ='X';
		}

		printf("Privileges: %c%c%c", read, write, execute);

		printf("Date created: %d", node->date_of_create);

		printf("Date last accessed: %d", node->date_last_accessed);

		printf("Date last modified: %d", node->date_last_modified);

		printf("File owner: %d", node->file_owner);

		printf("Last user modified: %d", node->last_user_modified);

		printf("File size: %d", node->file_size);

		printf("Index Block Location: %d", node->location);

		if(node->encrypted == true)
		{
			printf("Encrypted: True");
		}
		else
		{
			printf("Encrypted: False");
		}

		printf("Check sum: %d", node->check_sum);


		return 1;
	}
	return 0;
}
