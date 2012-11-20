#include "glob_data.h"

#ifndef BLOCKIO_H_
#define BLOCKIO_H_

extern int
get_block(int blknum,    /* which disk block to retrieve */
	  byte *buf);    /* where in memory to put retrieved data */

extern int
put_block(int blknum,    /* which disk block to update */
	  byte *buf);    /* where in memory to get new disk block contents */

#endif /* BLOCKIO_H_ */
