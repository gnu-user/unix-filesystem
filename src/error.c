/*
 * error.c
 *
 *  Created on: Nov 25, 2012
 *      Author: ubuntu
 */

#include "error.h"

int printerror(error_code errorno) {
	switch (errorno) {
	case SUCCESS:
		///No need to print anything if successful.
		//printf("Success!");
		break;
	case INVALID_PARAMETER:
		printf("Invalid parameter specified.");
		break;
	case DISK_READ_ERROR:
		printf("Disk read i/o error.");
		break;
	case DISK_WRITE_ERROR:
		printf("Disk write i/o error.");
		break;
	case FILE_NOT_FOUND:
		printf("File not found at path specified.");
		break;
	case INVALID_FILE_TYPE:
		printf("Invalid file type specified.");
		break;
	case INVALID_FILE_NAME:
		printf("Invalid file name specified.");
		break;
	case INVALID_FILE_DESCRIPTOR:
		printf("Invalid file descriptor.");
		break;
	case INVALID_PATH:
		printf("Invalid path specified.");
		break;
	case INVALID_PATH_LENGTH:
		printf("Invalid path length specified. (>6 characters)");
		break;
	case INSUFFICIENT_DISK_SPACE:
		printf("Insufficient disk space to complete operation.");
		break;
	case ERROR_UPDATING_SB:
		printf("Fatal error updating super block.");
		exit(ERROR_UPDATING_SB);
		break;
	case ERROR_UPDATING_FBL:
		printf("Fatal error updating free block list.");
		exit(ERROR_UPDATING_FBL);
		break;
	case ERROR_UPDATING_SWOFT:
		printf("Error updating system wide open file table.");
		break;
	case INDEX_ALLOCATION_ERROR:
		printf("Corrupted index block, or index/link allocation error.");
		break;
	case ERROR_BLOCK_LINKAGE:
		printf("Corrupted block linkage, or block linkage error.");
		break;
	case ERROR_BUFFER_SEGMENTATION:
		printf("Buffer segmentation error. (This is not a segmentation fault!)");
		break;
	case PARENT_NOT_FOUND:
		printf("Node parent not found.");
		break;
	case DIRECTORY_HAS_CHILDREN:
		printf("Directory has children.");
		break;
	case DIRECTORY_TRAVERSED:
		printf("Directory content traversal completed.");
		break;
	case DIRECTORY_EMPTY:
		printf("Directory contents empty.");
		break;
	case FILE_EMPTY:
		printf("File contents empty.");
		break;
	case FILE_PAST_EOF:
		printf("Attempted read/write past end of file.");
		break;
	default:
		printf("Unknown error occurred.");
		break;
	}

	return 0;
}
