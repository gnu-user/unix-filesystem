#include "system_open_file_table.h"
#include "traverse_tree.h"
#include "open_file.h"

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

	//TODO fix open error when file not found (it might be seg faulting, program just crashed)
	uint32_t* inode_location = NULL;
	char** tokens = NULL;

	/**
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		/**
		 * Invalid path name
		 * TODO validate this error code
		 */
		print_error(INVALID_PATH);
		return -2;
	}

	/**
	 * Traverse the file system to find the desired inode
	 */
	if(tokens[0] == NULL)
	{
		inode_location = calloc(2, sizeof(uint32_t));
		inode_location[0] = get_root();
		if(inode_location[0] < 0)
		{
			/**
			 * Read Error
			 * TODO validate this error code
			 */
			print_error(DISK_READ_ERROR);
			return -1;
		}
	}
	else{
		inode_location = traverse_file_system(tokens, false);
	}

	if(inode_location == NULL)
	{
		/**
		 * Invalid path or file/directory not found
		 * TODO validate this error code
		 */
		print_error(FILE_NOT_FOUND);
		return -1;
	}

	/**
	 * TODO decide if open constitutes accessing a file
	 * if successful open
	 * update last date accessed
	 */

	/**
	 * Retrieve the Inode of the desired file.
	 * Create file descriptor.
	 * Return file descriptor.
	 */
	return show_information(add_to_swoft(inode_location[0]));
}

/**
 * The all of the information stored in the given file descriptor's Inode.
 *
 * @param fd integer, the file descriptor.
 *
 * @return an integer value, Adjusted to output the fd if success to allow for
 * it to be used on the return line
 * if the value >= 0 then the function is successful
 * if the value < 0 then the function is unsuccessful
 */
int show_information(int fd)
{
	if(fd >= 0)
	{
		/**
		 * Get the Inode from the swoft given the fd
		 */
		inode node = get_swoft_inode(fd);

		printf("Name: %s\n", node.name);
		if(node.type == true)
		{
			printf("Type: directory\n");
		}
		else
		{
			printf("Type: file\n");
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

		printf("Privileges: %c%c%c\n", read, write, execute);

		printf("Date created: %d\n", node.date_of_create);

		printf("Date last accessed: %d\n", node.date_last_accessed);

		printf("Date last modified: %d\n", node.date_last_modified);

		printf("File owner: %d\n", node.file_owner);

		printf("Last user modified: %d\n", node.last_user_modified);

		printf("File size: %d\n", node.file_size);

		printf("Index Block Location: %d\n", node.location);

		if(node.encrypted == true)
		{
			printf("Encrypted: True\n");
		}
		else
		{
			printf("Encrypted: False\n");
		}

		printf("Check sum: %d\n", node.check_sum);

		printf("Uuid: %s\n", node.uuid);

		/**
		 * TODO validate that this is the correct return (fd) ?
		 */
		print_error(SUCCESS);
		return fd;
	}

	/**
	 * Invalid file descriptor.
	 * TODO validate this error code
	 */
	print_error(INVALID_FILE_DESCRIPTOR)
	return -1;
}
