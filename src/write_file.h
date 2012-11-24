/*
 * write_file.h
 *
 *  Created on: Nov 23, 2012
 *      Author: jon
 */

#ifndef WRITE_FILE_H_
#define WRITE_FILE_H_

/**
 * if start >= then actual data is inserted (overrides) from start for the
 * length of actual data.
 * if start == -1 then actual data is appended to the end of the databuf
 *
 * @return databuf containing actual_data
 */
extern block* modify_data(uint32_t start, uint32_t length, byte* data_buf, byte* actual_data);


/**
 * Takes a data buffer and returns an array of blocks, it is similar to modify_data
 * except that no data is actually being modified.
 *
 * @param data_buf A buffer containing the data to be segmented into blocks
 * @param length The length of the buffer to be segmented into blocks
 *
 * @return A null terminated array of blocks.
 */
extern block* segment_data(byte* data_buf, uint32_t length);


/** sfs_write
 * Write the length bytes of data specified from a memory location to the
 * specified file. The parameter start gives the offset of the first byte in
 * the file that should be copied to. Alternatively, the value of start may be
 * set to -1, this indicates that the specified number of bytes should be
 * appended to the file. Appending (setting start to -1) is the only allowable
 * way to increase the length of a file.
 *
 * @param fd A file descriptor for the file to write data to
 * @param start The offset of the first byte in the file that should be written
 * to, if start is -1 then the data will be appended to the file
 * @param length The length of bytes of data to be written to the file
 * @param mem_pointer The memory location containing the bytes to write to file
 *
 * @return an integer value,
 * If the value > 0 the file write was a success
 * If the value <= 0 the file write was unsuccessful
 *
 * @exception INVALID_FILE_DESCRIPTOR If the file descriptor specified does not
 * exist
 *
 * @exception INSUFFICIENT_DISK_SPACE If the length of the blocks to be written
 * is greater than the amount of available blocks on disk
 */
extern int sfs_write(int fd, int start, int length, byte *mem_pointer);






#endif /* WRITE_FILE_H_ */
