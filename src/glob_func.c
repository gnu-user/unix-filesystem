/**
 * Contains an aggregate collection of globally accessible functions
 */
#include "glob_data.h"
#include "glob_func.h"
#include <stdio.h>
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

	buf2 = calloc(size2, sizeof(byte));

	if(buf2 == NULL)
	{
		return NULL;
	}
	buf2 = memcpy(buf2, buf1, size1);

	return buf2;
}

