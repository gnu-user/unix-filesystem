#include "block_func.h"

int write_block(uint32_t location, byte* buf)
{
	return put_block(location, buf);
}

int read_block(uint32_t location, byte* buf)
{
	return get_block(location, buf);
}
