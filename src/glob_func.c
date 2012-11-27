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


#include "glob_data.h"
#include "glob_func.h"
#include <stdlib.h>
#include <stdbool.h>
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


uint32_t calc_num_bytes(byte*buf)
{
	uint32_t i = 0;
	while(buf[i] != NULL)
	{
		i++;
	}

	return i;
}


uint32_t calc_num_blocks(byte* buf)
{
	/* Error occurred the buffer is larger than MAX_IO_LENGTH */
	uint32_t c = (uint32_t) ceil((double)(calc_num_bytes(buf))/BLKSIZE);
	return c;
}


/* NOTE a prime example of when static type systems break down in generic programming */
void* concat(void* src_1, void* src_2, uint32_t size)
{
	uint32_t i = 0, j = 0;
	/* Number of null characters, for null terminated data it's length of size */
	uint32_t num_null = 0;

	/* Cast each pointer to a byte* for byte-by-byte concatenation
	 * using pointer arithmetic
	 */
	byte* _src_1 = (byte*) src_1;
	byte* _src_2 = (byte*) src_2;
	void* result = NULL;


	/* Get the number of items in each array using the size as an index multiplier.
	 * In order to check for NULL have to verify that all bytes given the size of data
	 * contain NULL, for example the NULL character for uint32_t is 00 00 00 00
	 */
	if (_src_1 != NULL)
	{
		while (true)
		{
			num_null = 0;

			for (uint32_t k = 0; k < size; ++k)
			{
				if (_src_1[(i * size) + k] == NULL)
				{
					++num_null;
				}
			}

			/* Reached the NULL character for data type */
			if (num_null == size)
			{
				break;
			}

			/* Increment counter for number of items in array */
			++i;
		}
	}

	if (_src_2 != NULL)
	{
		while (true)
		{
			num_null = 0;

			for (uint32_t k = 0; k < size; ++k)
			{
				if (_src_2[(j * size) + k] == NULL)
				{
					++num_null;
				}
			}

			/* Reached the NULL character for data type */
			if (num_null == size)
			{
				break;
			}

			/* Increment counter for number of items in array */
			++j;
		}
	}

	/* Create a new NULL terminated buffer to hold the concatenation results */
	result = calloc(i+j+1, size);

	/* Perform the concatenation, store the results in result, use pointer arithmetic for
	 * the offset of the first item in order to concatenate the second item to it
	 */
	memcpy(result, src_1, i * size);
	memcpy((result + (i * size)), src_2, j * size);

	return result;
}


void* concat_len(void* src_1, void* src_2, uint32_t size, uint32_t len)
{
	uint32_t i = 0;
	/* Number of null characters, for null terminated data it's length of size */
	uint32_t num_null = 0;

	/* Cast each pointer to a byte* for byte-by-byte concatenation
	 * using pointer arithmetic
	 */
	byte* _src_1 = (byte*) src_1;
	void* result = NULL;


	/* Get the number of items in each array using the size as an index multiplier
	 *
	 * In order to check for NULL have to verify that all bytes give the size of data
	 * contain NULL, for example the NULL character for uint32_t is 00 00 00 00
	 */
	if (_src_1 != NULL)
	{
		while (true)
		{
			num_null = 0;

			for (uint32_t k = 0; k < size; ++k)
			{
				if (_src_1[(i * size) + k] == NULL)
				{
					++num_null;
				}
			}

			/* Reached the NULL character for data type */
			if (num_null == size)
			{
				break;
			}

			/* Increment counter for number of items in array */
			++i;
		}
	}

	/* Create a new NULL terminated buffer to hold the concatenation results */
	result = calloc((i * size) + size + len, sizeof(byte));

	/* Perform the concatenation, store the results in result, use pointer arithmetic for
	 * the offset of the first item to concatenate the second item to
	 */
	memcpy(result, src_1, i * size);
	memcpy((result + (i * size)), src_2, len);

	return result;
}


char** tokenize_path(char* pathname)
{
	/*  NULL initialize the tokenizer pointer and 2D array of tokens */
	char* ptr_tkn = NULL;
	char** tokens = NULL;
	uint32_t num_tokens = 0;

	/* Validate the pathname before tokenizing */
	if (!validate_path(pathname))
	{
		return NULL;
	}

	/* Get the first token */
	ptr_tkn = strtok(pathname, "/");

	/* Copy the tokens into an array of tokens */
	while (ptr_tkn != NULL)
	{
		/* Increase the tokens array size for an additional token */
		tokens = (char**) realloc(tokens, ++num_tokens * sizeof(char*));

		/* Copy the token into the array */
		tokens[num_tokens - 1] = (char*) calloc(strlen(ptr_tkn), sizeof(char*));
		strncpy(tokens[num_tokens - 1], ptr_tkn, strlen(ptr_tkn));

		ptr_tkn = strtok(NULL, "/");
	}

	/* Increase the tokens array size for a final NULL termination token */
	tokens = (char**) realloc(tokens, ++num_tokens * sizeof(char*));
	tokens[num_tokens - 1] = NULL;

	/* Validate the tokens before returning the tokens array, return NULL if any
	 * of the tokens are invalid
	 */
	if (!validate_tokens(tokens))
	{
		/* Free the memory allocated for tokens */
		free_tokens(tokens);
		return NULL;
	}

	return tokens;
}


static bool validate_path(char* pathname)
{
	/* NULL pathname, error */
	if (pathname == NULL)
	{
		return false;
	}

	/* Error if the pathname contains multiple path delimiters */
	if (strstr(pathname, "//") != NULL)
	{
		return false;
	}

	if(strncmp(pathname, "/", 1) != 0)
	{
		return false;
	}

	return true;
}


static bool validate_tokens(char** tokens)
{
	/* Validate the path by checking each token against a set of conditions */
	uint32_t i = 0;
	while (tokens[i] != NULL)
	{
		/* Error If the token is greater than MAX_NAME_LEN */
		if (strlen(tokens[i]) > MAX_NAME_LEN)
		{
			return false;
		}

		/* Error if token contains a space character */
		if (strchr(tokens[i], ' ') != NULL)
		{
			return false;
		}
		++i;
	}

	return true;
}


bool free_tokens(char **tokens)
{
	uint32_t i = 0;

	/* Free the memory allocated for each of the tokens in the 2D array */
	if (tokens != NULL)
	{
		while (tokens[i] != NULL)
		{
			free(tokens[i]);
			++i;
		}
		free(tokens);
	}
	else
	{
		return false;
	}
	return true;
}
