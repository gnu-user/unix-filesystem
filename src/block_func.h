#include "blockio.h"
#include "glob_data.h"

#ifndef BLOCK_FUNC_H_
#define BLOCK_FUNC_H_

extern int write_block(uint32_t location, byte* buf);

extern int read_block(uint32_t location, byte* buf);

#endif /* BLOCK_FUNC_H_ */
