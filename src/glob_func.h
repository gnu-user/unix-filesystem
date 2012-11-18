/*
 * glob_func.h
 *
 * Contains an aggregate collection of globally accessible functions
 *
 */
#include "glob_data.h"

#ifndef GLOB_FUNC_H_
#define GLOB_FUNC_H_

extern byte write_buffer[BLKSIZE];

extern byte read_buffer[BLKSIZE];

extern byte* allocate_buf(byte* buf, uint32_t size);

extern byte* copy_to_buf(byte* buf1, byte* buf2, uint32_t size1, uint32_t size2);

#endif /* GLOB_FUNC_H_ */
