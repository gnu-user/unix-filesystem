#include "glob_data.h"
#include "error.h"

#ifndef BLOCKIO_H_
#define BLOCKIO_H_

extern int
get_block(uint32_t blknum,    /* which disk block to retrieve */
	  byte *buf);    /* where in memory to put retrieved data */

extern int
put_block(uint32_t blknum,    /* which disk block to update */
	  byte *buf);    /* where in memory to get new disk block contents */

#endif /* BLOCKIO_H_ */
