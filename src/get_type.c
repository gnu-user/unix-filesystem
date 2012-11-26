#include "blockio.h"
#include "traverse_tree.h"
#include "get_type.h"

/** sfs_gettype
 * Get the type of the file with the pathname specified.
 *
 * @param pathname The pathname of file to create, must be full directory path
 *
 * @return the file type of the given file
 * If the file type >= 0 then the file type retrieval is a success
 * 	If the file type is 0, or 1 then it is a file, directory respectively
 * 	If the file type > 1 then the file is not known
 * If the file type < 0 then the file type retrieval has failed
 *
 * @exception FILE_NOT_FOUND If the pathname does not already exist
 */
int sfs_gettype(char *pathname)
{
	//TODO test gettype
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
		return 0;
	}
	/**
	 * Traverse the file system to find the desired inode
	 */
	inode_location = traverse_file_system(tokens, false);

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
	 * Retrieve the file type from the Inode
	 * return the file type from the Inode
	 *
	 * TODO validate this error code
	 * TODO make this use proper error handling
	 */
	print_error(UNKNOWN);
	return get_type(inode_location[0]);
}
