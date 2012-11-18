/*
 * glob_data.h
 *
 *  Created on: 2012-11-14
 *      Author: joseph
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef GLOBDATA_H_
#define GLOBDATA_H_

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512
/* number of files that can be open at once */
#define NUMOFL	  32

#define SUPER_BLOCK	0
#define FREE_BLOCK 	3
#define FREE_INDEX 	2
#define ROOT_DIR 	2

typedef uint8_t byte;

#endif /* GLOBDATA_H_ */
