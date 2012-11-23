#include "glob_data.h"
#include "blockio.h"
#include "index_block.h"
#include "system_open_file_table.h"

/** sfs_readdir
 * Reads the file name components from a directory file. The first time
 * sfs_readdir is called, the first file name component in the directory will be
 * placed into memory at the location pointed to by mem_pointer. Each successive
 * call to sfs_readdir will place the next name component from the directory into
 * the mem_pointer buffer. When all names have been returned, sfs_readdir will
 * place nothing in the buffer, and return a value of zero to indicate the
 * directory has been completely scanned.
 *
 * @param fd A file descriptor for the file to read data from
 * @param mem_pointer The memory location to store the file name components
 *
 * @return an integer value
 * If the value > 0 the read dir was a success
 * If the value = 0 if there is no contents in dir
 * If the value < 0 the read dir was unsuccessful
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 */
int sfs_readdir(int fd, byte *mem_pointer)
{
	//TODO test readdir
	inode directory = get_null_inode();
	locations index_block = NULL;
	if(fd >= 0)
	{

		/**
		 * Validate the file descriptor
		 */
		if(validate_fd(fd) > 0)
		{
			/**
			 * file descriptor not found in swoft
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return -1;
		}

		/**
		 * Retrieve the contents of the directory's index block. Use the Inode
		 * to retrieve the names of the contents. Store the values into
		 * mem_pointer.
		 */
		directory = get_swoft_inode(fd);

		/**
		 * If the inode is not a directory return an error
		 */
		if(directory.type != 1)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return -1;
		}

		/**
		 * Iterate through the index block
		 * TODO ensure that iterate_index returns a null value for index_block
		 * when the directory is empty
		 */
		iterate_index(directory.location, index_block);

		/**
		 * TODO decided if directory is access if a user reads it or if a
		 * user reads any file below it
		 * Update last_accessed
		 */
		mem_pointer = (char*) index_block;

		/**
		 * return value > 0 for a successful read dir
		 * return value = 0 if there is no contents in dir
		 * return value < 0 for a unsuccessful read dir
		 */
		if(mem_pointer == NULL)
		{
			/**
			 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
			 */
			return 0;
		}
		/**
		 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
		 */
		return 1;
	}

	/**
	 * TODO REPLACE THIS ERROR VALUE WITH A GENERIC ERROR ENUM
	 */
	return -1;
}
