/*
 * read_file.h
 *
 *  Created on: Nov 24, 2012
 *      Author: ubuntu
 */

#include "error.h"

#ifndef READ_FILE_H_
#define READ_FILE_H_


/**
 * @brief Read the contents of a file.
 *
 * @details Copy the length of bytes of data specified from a regular file to memory
 * location specified by mem_pointer. The parameter start gives the offset
 * of the first byte in the file that should be copied.
 *
 * @param fd A file descriptor for the file to read data from.
 *
 * @param start The offset of the first byte in the file that should be copied.
 *
 * @param length The length of bytes of data to copy from the file.
 *
 * @param mem_pointer The memory location to store the data read from the file.
 *
 * @return Returns an integer value, if the value > 0 then the file was
 * read successfully. If the value <= 0 then the file failed to be read.
 *
 * @exception FILE_LENGTH_OVERRUN If the file cannot be read correctly because
 * the length of bytes specified exceeds the length of the file, no data will be
 * copied from the file if an overrun occurs.
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_read(int fd, int start, int length, byte *mem_pointer);


#endif /* READ_FILE_H_ */
