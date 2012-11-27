/*
 * SneakyFS - A Secure UNIX File System
 *
 * Copyright (C) 2012, Jonathan Gillett, Joseph Heron, and Daniel Smullen
 * All rights reserved.
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "block_func.h"

int write_block(uint32_t location, byte* buf)
{
	return put_block(location, buf);
}

int read_block(uint32_t location, byte* buf)
{
	return get_block(location, buf);
}

byte* get_data(locations location)
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
