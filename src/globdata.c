#include "globdata.h"
#include <stdlib.h>
#include <string.h>

char* allocate_buf(char* buf, uint32_t size)
{
	buf = (char *) calloc(size, sizeof(char));
	return buf;
}

char* copy_to_buf(void* buf1, char* buf2, uint32_t size1, uint32_t size2)
{
	if(size1 > size2 || buf1 == NULL)
	{
		return NULL;
	}

	buf2 = (char *) calloc(size2, sizeof(char));

	if(buf2 == NULL)
	{
		return NULL;
	}
	memcpy(buf2, buf1, size1);

	return buf2;
}
