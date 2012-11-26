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


#ifndef ERROR_H_
#define ERROR_H_

/**
 * @enum error_code
 *
 * @brief List of error codes with name definitions.
 *
 * @details Contains a list of constant integers used as error codes
 * with a human-readable name definitions.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
typedef enum
{
	SUCCESS, 					/** No error occurred, execution was successful. */
	INVALID_PARAMETER, 			/** An invalid parameter was given to the function. */
	DISK_READ_ERROR,			/** A block of data could not be read from disk. */
	DISK_WRITE_ERROR, 			/** A block of data could not be written to disk. */
	FILE_NOT_FOUND,				/** The specified file could not be found on disk. */
	INVALID_FILE_TYPE,			/** The file type specified is invalid. */
	INVALID_FILE_NAME,			/** The file name specified is invalid. */
	INVALID_FILE_DESCRIPTOR,	/** The file descriptor specified is invalid or does not exist. */
	INVALID_PATH,				/** The path specified is invalid. */
	INVALID_PATH_LENGTH,		/** The path length given is too long, path tokens cannot be longer than 6 characters. */
	INSUFFICIENT_DISK_SPACE,	/** The requested operation does not have sufficient blocks available on disk to complete execution. */
	ERROR_UPDATING_SB, 			/** Fatal error: The super block could not be updated. The file system or disk are corrupted. */
	ERROR_UPDATING_FBL, 		/** Fatal error: The free block list could not be updated. The file system or disk may be corrupted. */
	ERROR_UPDATING_SWOFT,		/** The system-wide open file table cannot be updated. This may be indicative of memory corruption. */
	INDEX_ALLOCATION_ERROR,		/** The given index block data structure is corrupted, invalid, or empty. */
	ERROR_BLOCK_LINKAGE,		/** An error occurred concerning the linkage of an inode to an index block structure. */
	ERROR_BUFFER_SEGMENTATION,	/** An error occurred segmenting a buffer into block-sized chunks. */
	PARENT_NOT_FOUND,			/** An inode has become loose, and its parent cannot be found. */
	DIRECTORY_HAS_CHILDREN,		/** An attempt was made to delete a directory which has children. Directories must be empty to be deleted. */
	DIRECTORY_TRAVERSED,		/** A directory was fully traversed. Further attempts to read the contents of the directory will begin from the top of the structure. */
	DIRECTORY_EMPTY,			/** An attempt was made to read the contents of an empty directory. */
	FILE_EMPTY,					/** An attempt was made to perform operations on a file which contains no data. */
	FILE_PAST_EOF,				/** An attempt was made to write to a file past the current length of the file, without appending. Appending is the only allowed way to increase the length of a file.*/
	UNKNOWN 					/** An unknown error occurred. */
} error_code;

/**
 * @brief Prints an error code.
 *
 * @details Outputs the specified error code to the console. Fatal errors will cause the application
 * to terminate immediately to prevent file system or disk corruption.
 *
 * @param The specified error to output.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern void print_error(error_code errorno);

#endif /* ERROR_H_ */
