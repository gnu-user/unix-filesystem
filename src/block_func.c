#include "block_func.h"

int write_block(uint32_t location, byte* buf)
{
	return put_block(location, buf);
}

int read_block(uint32_t location, byte* buf)
{
	return get_block(location, buf);
}

/**
 * TODO add decrypt block
 */
byte* get_data(uint32_t* location)
{
	int i = 0;
	byte* databuf = NULL;
	byte* temp = NULL;
	byte* buf = NULL;
	int retval = 0;

	while(location[i] != NULL)
	{
		buf = allocate_buf(buf, BLKSIZE);

		retval = read_block(location[i], buf);
		if(retval != 0)
		{
			return NULL;
		}
		temp = (byte*) concat_len(databuf, buf, sizeof(byte), BLKSIZE);
		free(databuf);
		free(buf);
		databuf = temp;

		i++;
	}
	return databuf;
}
