/*
 * globdata.h
 *
 *  Created on: 2012-11-14
 *      Author: joseph
 */

#include <stdint.h>

#ifndef GLOBDATA_H_
#define GLOBDATA_H_

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512

extern char write_buffer[BLKSIZE];

extern char read_buffer[BLKSIZE];

extern char* allocate_buf(char* buf, uint32_t size);

extern char* copy_to_buf(char* buf1, char* buf2, uint32_t size1, uint32_t size2);

#endif /* GLOBDATA_H_ */
