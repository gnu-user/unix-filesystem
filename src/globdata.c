#include "globdata.h"
#include <stdlib.h>
#include <string.h>

byte* allocate_buf(byte* buf, uint32_t size)
{
	buf = (byte *) calloc(size, sizeof(byte));
	return buf;
}

byte* copy_to_buf(byte* buf1, byte* buf2, uint32_t size1, uint32_t size2)
{
	if(size1 > size2 || buf1 == NULL)
	{
		return NULL;
	}

	buf2 = (byte *) calloc(size2, sizeof(byte));

	if(buf2 == NULL)
	{
		return NULL;
	}
	memcpy(buf2, buf1, size1);

	return buf2;
}


/**
 * System wide open file table
 * Needs to have at least 5 instances (to have 5 files open at once)
 **/

