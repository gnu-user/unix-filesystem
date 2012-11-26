#include "blockio.h"
#include "glob_data.h"
#include "error.h"

#ifndef BLOCK_FUNC_H_
#define BLOCK_FUNC_H_

/**
 * A wrapper for put_block
 *
 * @param location the location on disk for the buf to be written to
 * @param the buffer to store on disk
 *
 * @return an integer value
 * if value >= 0 success
 * otherwise failure
 */
extern int write_block(uint32_t location, byte* buf);

/**
 * A wrapper for get_block
 *
 * @param location the location on disk for the buf to be written to
 * @param the buffer to store on disk
 *
 * @return an integer value
 * if value >= 0 success
 * otherwise failure
 */
extern int read_block(uint32_t location, byte* buf);

/**
 * Get the data blocks and concat them into a large byte buffer
 *
 * @param the locations of the data blocks on disk
 *
 * @return the data_buffer containing all of the bytes of data.
 */
extern byte* get_data(locations location);

#endif /* BLOCK_FUNC_H_ */
