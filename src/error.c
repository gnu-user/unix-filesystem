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


#include "error.h"

void print_error(error_code errorno) {
	switch (errorno) {
	case SUCCESS:
		///No need to print anything if successful.
		//printf("Success!\n");
		break;
	case INVALID_PARAMETER:
		printf("Invalid parameter specified.\n");
		break;
	case DISK_READ_ERROR:
		printf("Disk read i/o error.\n");
		break;
	case DISK_WRITE_ERROR:
		printf("Disk write i/o error.\n");
		break;
	case FILE_NOT_FOUND:
		printf("File not found at path specified.\n");
		break;
	case INVALID_FILE_TYPE:
		printf("Invalid file type specified.\n");
		break;
	case INVALID_FILE_NAME:
		printf("Invalid file name specified.\n");
		break;
	case INVALID_FILE_DESCRIPTOR:
		printf("Invalid file descriptor.\n");
		break;
	case INVALID_PATH:
		printf("Invalid path specified.\n");
		break;
	case INVALID_PATH_LENGTH:
		printf("Invalid path length specified. (>6 characters)\n");
		break;
	case INSUFFICIENT_DISK_SPACE:
		printf("Insufficient disk space to complete operation.\n");
		break;
	case ERROR_UPDATING_SB:
		printf("Fatal error updating super block.\n");
		exit(ERROR_UPDATING_SB);
		break;
	case ERROR_UPDATING_FBL:
		printf("Fatal error updating free block list.\n");
		exit(ERROR_UPDATING_FBL);
		break;
	case ERROR_UPDATING_SWOFT:
		printf("Error updating system wide open file table.\n");
		break;
	case INDEX_ALLOCATION_ERROR:
		printf("Corrupted index block, or index/link allocation error.\n");
		break;
	case ERROR_BLOCK_LINKAGE:
		printf("Corrupted block linkage, or block linkage error.\n");
		break;
	case ERROR_BUFFER_SEGMENTATION:
		printf("Buffer segmentation error. (This is not a segmentation fault!)\n");
		break;
	case PARENT_NOT_FOUND:
		printf("Node parent not found.\n");
		break;
	case DIRECTORY_HAS_CHILDREN:
		printf("Directory has children.\n");
		break;
	case DIRECTORY_TRAVERSED:
		printf("Directory content traversal completed.\n");
		break;
	case DIRECTORY_EMPTY:
		printf("Directory contents empty.\n");
		break;
	case FILE_EMPTY:
		printf("File contents empty.\n");
		break;
	case FILE_PAST_EOF:
		printf("Attempted read/write past end of file.\n");
		break;
	default:
		printf("Unknown error occurred.\n");
		break;
	}
}
