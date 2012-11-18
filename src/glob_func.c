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

// NOTE a prime example of when static type systems break down in generic programming
void* concat(void* dest, void* src, uint32_t size)
{
	/* UNDEFINED if dest OR src NULL */
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}

	/* Cast each pointer to a byte* for byte-by-byte concatenation
	 * using pointer arithmetic
	 */
	uint32_t i = 0, j = 0;
	byte* _dest = (byte*) dest;
	byte* _src = (byte*) src;

	/* Get the number of items in each array using the size as an index multiplier */
	while (_dest[i * size] != NULL)
	{
		++i;
	}
	while (_src[j * size] != NULL)
	{
		++j;
	}

	/* Reallocate dest to contain the results using size as a multiplier */
	dest = realloc(dest, ((i+j+1) * size));
	_dest = (byte *) dest;

	if (_dest != NULL)
	{
		/* Concatenate the two arrays using byte-by-byte concatenation */
		for (uint32_t k = i * size; k < (i+j+1) * size; ++k)
		{
			_dest[k] = _src[k - (i * size)];
		}
	}
	else
	{
		return NULL;
	}

	/* Free the memory used by src and return dest pointer */
	free(src);
	return dest;
}
