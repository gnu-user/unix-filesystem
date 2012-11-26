#include "blockio.h"
#include "glob_data.h"
#include "error.h"

#ifndef BLOCK_FUNC_H_
#define BLOCK_FUNC_H_


/**
 * @brief A wrapper for the put_block function.
 *
 * @param location The location on disk for the buffer to be written to.
 *
 * @param The buffer to store on disk.
 *
 * @return Returns an integer value. If the value >= 0, the function
 * was successful. Otherwise, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int write_block(uint32_t location, byte* buf);


/**
 * @brief A wrapper for the get_block function.
 *
 * @param location The location on disk for the buffer to be written to.
 *
 * @param The buffer to store on disk.
 *
 * @return Returns an integer value. If the value >= 0 the function
 * was successful. Otherwise, the function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int read_block(uint32_t location, byte* buf);


/**
 * @brief Get the data blocks and concatenate them into a large byte buffer.
 *
 * @param location The locations of the data blocks on disk.
 *
 * @return Returns the data_buffer containing all of the bytes of data.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern byte* get_data(locations location);

#endif /* BLOCK_FUNC_H_ */
