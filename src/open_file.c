/*
 * SneakyFS - A Secure UNIX File System
 *
 * Copyright (C) 2012, Jonathan Gillett, Joseph Heron, and Daniel Smullen
 * All rights reserved.
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
	//TODO fix open error when file not found (it might be seg faulting, program just crashed)
	uint32_t* inode_location = NULL;
	char** tokens = NULL;
	inode* node = NULL;
	byte* buf = NULL;

	/*
	 * Parse the pathname
	 */
	tokens = tokenize_path(pathname);
	if(tokens == NULL)
	{
		/*
		 * Invalid path name
		 * TODO validate this error code
		 */
		print_error(INVALID_PATH);
		return -2;
	}

	/*
	 * Traverse the file system to find the desired inode
	 */
	if(tokens[0] == NULL)
	{
		inode_location = calloc(2, sizeof(uint32_t));
		inode_location[0] = get_root();
		if(inode_location[0] < 0)
		{
			/*
			 * Read Error
			 * TODO validate this error code
			 */
			print_error(DISK_READ_ERROR);
			return -1;
		}
	}
	else
	{
		inode_location = traverse_file_system(tokens, false);
	}

	if(inode_location == NULL)
	{
		/*
		 * Invalid path or file/directory not found
		 * TODO validate this error code
		 */
		print_error(FILE_NOT_FOUND);
		return -1;
	}

	/* Get the inode from disk and update the last_accessed date in the inode */
	node = get_inode(inode_location[0]);

	if (node == NULL)
	{
		/*
		 * Read Error
		 * TODO validate this error code
		 */
		print_error(DISK_READ_ERROR);
		return -1;
	}

	/* Update the date last accessed and write the inode back to disk */
	node->date_last_accessed = time(NULL);

	buf = allocate_buf(buf, BLKSIZE);
	buf = (byte *) copy_to_buf((byte *) node, (byte *) buf, sizeof(inode), BLKSIZE);

	if(write_block(inode_location[0], buf) < 0)
	{
		/*
		 * TODO validate this error code
		 */
		print_error(DISK_WRITE_ERROR);
		return -1;
	}

	/*
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
	char str[100];
	struct tm * local_time;

	if(fd >= 0)
	{
		/*
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

		/* Convert the POSIX times into the local time and print the ASCII version */
		local_time = localtime(&node.date_of_create);
		printf("Date created: %s", asctime(local_time));

		local_time = localtime(&node.date_last_accessed);
		printf("Date last accessed: %s", asctime(local_time));

		local_time = localtime(&node.date_last_modified);
		printf("Date last modified: %s", asctime(local_time));

		if(node.type == false)
		{
			printf("File owner: %d\n", node.file_owner);
		}

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

		uuid_unparse(node.uuid, str);
		printf("Uuid: %s\n", str);

		/*
		 * TODO validate that this is the correct return (fd)
		 */
		print_error(SUCCESS);
		return fd;
	}

	/*
	 * Invalid file descriptor.
	 * TODO validate this error code
	 */
	print_error(INVALID_FILE_DESCRIPTOR);
	return -1;
}
