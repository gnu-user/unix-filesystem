#include "glob_data.h"
#include "error.h"

#ifndef BLOCKIO_H_
#define BLOCKIO_H_

/**
 * @brief Retrieves a block from disk.
 *
 * @param blknum Which disk block to retrieve.
 *
 * @param buf Where in memory to put the retrieved data.
 */
extern int get_block(uint32_t blknum, byte *buf);

/**
 * @brief Writes a block to disk.
 *
 * @param blknum Which disk block to update.
 *
 * @param buf Where in memory to get new disk block contents.
 */
extern int put_block(uint32_t blknum, byte *buf);

#endif /* BLOCKIO_H_ */
