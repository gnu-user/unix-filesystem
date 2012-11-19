#include "I_node.h"
#include "system_open_file_table.h"
#include "traverse_tree.h"

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
	//TODO test open
	uint32_t* inode_location = NULL;
	char** tokens = NULL;

	/**
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		return 0;
	}

	/**
	 * Traverse the file system to find the desired inode
	 */
	inode_location = traverse_file_system(pathname, false);

	if(inode_location == NULL)
	{
		return -1;
	}

	/**
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */

	return add_to_swoft(inode_location[0]);
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
		inode node = system_open_tb.fd[fd];

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
