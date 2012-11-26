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
typedef enum {
	SUCCESS,
	UNKNOWN,
	INVALID_PARAMETER,
	DISK_READ_ERROR,
	DISK_WRITE_ERROR,
	FILE_NOT_FOUND,
	INVALID_FILE_TYPE,
	INVALID_FILE_NAME,
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

extern void print_error(error_code errorno);

#endif /* ERROR_H_ */
