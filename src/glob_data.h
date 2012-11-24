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

/* This is the maximum number of bytes that can be read from
   or written to a file with a single file system call using this
   program.  Since files are limited to 512 bytes length, this should
   be sufficient. the format definition is necessary because macro
   substitutions do not take place within quoted strings
*/
#define MAX_IO_LENGTH   1024       /* I CHANGED IT FROM 512--->1024 */
#define IO_BUF_FORMAT   "%512s"

/* This is the maximum length of input strings (e.g., file names) read from
   the standard input.  This should be large enough for most purposes.
   the format definition is necessary because macro substitutions
   do not take place within quoted strings
*/
#define MAX_INPUT_LENGTH  512
#define INPUT_BUF_FORMAT  "%1024s"

/* Define if we are doing unit testing instead of executing sfs_test */
//#define UNIT_TESTING

/* size of blocks on simulated disk */
#define BLKSIZE  128
/* number of blocks on simulated disk */
#define NUMBLKS  512
/* number of files that can be open at once */
#define NUMOFL	  32
/* maximum length of a component in a pathname including the NULL char */
#define MAX_NAME_LEN 7

#define SUPER_BLOCK	 0

#define JOURNAL		1
//TODO ROOT needs to be put at the initial FBL_INDEX + number of FBL index blocks + number of FBL datablocks + 1
#define FBL_INDEX 2;

//TODO JON FIX THIS!!! NOW MONKEY!
//uint32_t ROOT = FBL_INDEX +	calc_index_blocks(ceil(NUMBLKS/BLKSIZE)) + get_num_datablocks(FBL_INDEX) + 1;

/* The TOTAL size of the FBL, including the overhead of the size of each index block
 * needed to index the FBL data blocks
 */
extern uint32_t FBL_TOTAL_SIZE;

extern uint32_t ROOT;


typedef uint8_t byte;

typedef byte block[BLKSIZE];

/* A NULL terminated array of locations for blocks on disk */
typedef uint32_t* locations;

#endif /* GLOBDATA_H_ */
