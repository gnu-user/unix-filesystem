/*
 * write_file.h
 *
 *  Created on: Nov 23, 2012
 *      Author: jon
 */

#include "error.h"

#ifndef WRITE_FILE_H_
#define WRITE_FILE_H_


/**
 * @brief Modifies or appends data in a buffer.
 *
 * @details Modifies the data in the buffer with the actual data
 * provided at the starting point and length of data specified.
 * If the starting value is -1 then the data is appended
 * to the buffer for the length specified.
 *
 * @note In order to provide support for appending data using start = -1, the parameter
 * type MUST be signed, which is int32_t.
 *
 * @param start The starting offset to alter the data at. If the value provided is -1,
 * append data to the end of the buffer. If start >= 0 then actual data is inserted
 * (overwrites) from start for the length of actual data.
 *
 * @param length The length of data to overwrite in the buffer, or to append to the buffer.
 *
 * @param data_buf A pointer to the data buffer to be altered or appended to.
 *
 * @param actual_data The data to overwrite the data buffer with or append to.
 *
 * @return Returns a null terminated array of blocks, if an error occurs
 * then NULL is returned.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern block* modify_data(int32_t start, uint32_t length, byte* data_buf, byte* actual_data);


/**
 * @brief Segments a buffer into block sized chunks of data.
 *
 * @details Takes a NULL terminated data buffer and returns an array of blocks, it is similar to
 * modify_data except that no data is actually being modified. Returns an array of blocks
 * where the last index is an entire empty block containing NULL. If an error occurs
 * NULL is returned.
 *
 * @param data_buf A NULL terminated buffer containing the data to be segmented into blocks.
 *
 * @return A null terminated array of blocks, where the last index is NULL,
 * if an error occurs then NULL is returned.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern block* segment_data(byte* data_buf);


/**
 * @brief Segments a buffer into block sized chunks of data.
 *
 * @details Takes a data buffer that in a multiple of BLKSIZE and returns an array of blocks,
 * it is similar to modify_data except that no data is actually being modified.
 * Returns a 2D array where each index in the array points a block, the last index
 * points to NULL. If an error occurs NULL is returned.
 *
 * @pre data_buf MUST be a buffer that is EXACTLY a multiple of BLKSIZE, it does not
 * necessarily need to be NULL terminated.
 *
 * @param data_buf A buffer containing the data to be segmented into blocks.
 *
 * @param length The length of the buffer in bytes to be segmented into blocks.
 *
 * @return Returns a null terminated array of blocks, where the last index is NULL,
 * if an error occurs then NULL is returned.
 */
extern block* segment_data_len(byte* data_buf, uint32_t length);


/**
 * @brief Write data to a file.
 *
 * @details Write the length bytes of data specified from a memory location to the
 * specified file. The parameter start gives the offset of the first byte in
 * the file that should be copied to. Alternatively, the value of start may be
 * set to -1, this indicates that the specified number of bytes should be
 * appended to the file. Appending (setting start to -1) is the only allowable
 * way to increase the length of a file.
 *
 * @param fd A file descriptor for the file to write data to.
 *
 * @param start The offset of the first byte in the file that should be written
 * to, if start is -1 then the data will be appended to the file.
 *
 * @param length The length of bytes of data to be written to the file.
 *
 * @param mem_pointer The memory location containing the bytes to write to file.
 *
 * @return Returns an integer value, if the value > 0 the file write was a
 * success, and if the value <= 0 the file write was unsuccessful.
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist or is invalid.
 *
 * @exception INSUFFICIENT_DISK_SPACE If the length of the blocks to be written
 * plus the size of the index overhead is greater than the amount of free
 * blocks on disk.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_write(int fd, int start, int length, byte *mem_pointer);


#endif /* WRITE_FILE_H_ */
