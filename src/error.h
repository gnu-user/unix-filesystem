/*
 * error.h
 *
 *  Created on: Nov 25, 2012
 *      Author: ubuntu
 */

#ifndef ERROR_H_
#define ERROR_H_

/**
* \enum Error_code enumeration
* Provides a list of constant integers used as error codes
* with a human-readable name definition.
*/
typedef enum
{
	SUCCESS,
	INVALID_PARAMETER,
	DISK_READ_ERROR,			///Probably a fatal error.
	DISK_WRITE_ERROR,			///Probably a fatal error.
	FILE_NOT_FOUND,
	INVALID_FILE_TYPE,
	INVALID_FILE_DESCRIPTOR,
	INVALID_PATH,
	INVALID_PATH_LENGTH,
	INSUFFICIENT_DISK_SPACE,
	ERROR_UPDATING_SB, 			///FATAL ERROR
	ERROR_UPDATING_FBL, 		///FATAL ERROR
	ERROR_UPDATING_SWOFT,
	INDEX_ALLOCATION_ERROR,
	ERROR_BLOCK_LINKAGE,
	ERROR_BUFFER_SEGMENTATION,
	PARENT_NOT_FOUND,
	DIRECTORY_HAS_CHILDREN,
	DIRECTORY_TRAVERSED,
	DIRECTORY_EMPTY,
	FILE_EMPTY,
	FILE_PAST_EOF
} error_code;

/*
extern char* error_message = {
		"Success!",
		"Invalid parameter specified.",
		"Disk read i/o error.",
		"Disk write i/o error.",
		"File not found at path specified.",
		"Invalid file type specified.",
		"Invalid file descriptor.",
		"Invalid path specified.",
		"Invalid path length specified. (>6 characters)",
		"Insufficient disk space to complete operation.",
		"Fatal error updating super block.",
		"Fatal error updating free block list.",
		"Error updating system wide open file table.",
		"Corrupted index block, or index/link allocation error.",
		"Corrupted block linkage, or block linkage error.",
		"Buffer contents segmentation error. (This is not a segmentation fault!)",
		"Node parent not found.",
		"Directory has children.",
		"Directory content traversal completed.",
		"Directory contents empty.",
		"File contents empty.",
		"Attempted read/write past end of file."
};
*/

#endif /* ERROR_H_ */
