/*
 * glob_func.h
 *
 * Contains an aggregate collection of globally accessible functions
 *
 */
#include "glob_data.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef GLOB_FUNC_H_
#define GLOB_FUNC_H_

extern byte write_buffer[BLKSIZE];

extern byte read_buffer[BLKSIZE];

extern byte* allocate_buf(byte* buf, uint32_t size);

extern byte* copy_to_buf(byte* buf1, byte* buf2, uint32_t size1, uint32_t size2);


/**
 * Concatenates two NULL termianted arrays, a src_1 and a src_2 array into a
 * single NULL terminated array containing the contents of both arrays. The
 * terminating NULL character in src_1 is overwritten by the first character of
 * src_2, and a NULL character is included at the end of the new array. A pointer
 * to the resulting array containing the contents of both arrays is then returned.
 *
 * @pre The arrays src_1 and src_2 MUST BE NULL TERMINATED
 * @pre The arrays to concatenate MUST contain the same data type for the concatenation
 * to function properly
 *
 * @param src_1 A pointer to a NULL terminated array
 * @param src_2 A pointer to a NULL terminated array
 * @param size The size in bytes of each item in the array
 *
 * @return A pointer to the resulting array containing the concatenated results
 */
extern void* concat(void* src_1, void* src_2, uint32_t size);


/**
 * TODO WRITE UNIT TEST & TEST FUNCTION
 * TODO Add support for checking that each component in the pathname is at most MAX_NAME_LEN
 *
 * Tokenizes the path provided into an array of tokens for each component in the path and
 * returns an array to a null terminated array of tokens.
 *
 * For example using pathname = "/foo/bar" the resulting tokens array would be
 *
 * [0]	=>	"foo"
 * [1]	=>	"bar"
 * [2]	=>	NULL
 *
 * @note If an error occurs a NULL pointer will be returned
 *
 * @pre Each component in the pathname must be at most (including the NULL
 * termination) MAX_NAME_LEN otherwise an error occurs, NULL pointer returned
 *
 * @param pathname  The pathname to tokenize
 *
 * @return A pointer to the 2D tokens array
 */
extern char** tokenize_path(char* pathname);


/**
 * TODO WRITE UNIT TEST & TEST FUNCTION
 *
 * Frees the memory allocated for the tokens
 *
 * @param tokens The NULL terminated 2D array filled with tokens to be freed
 *
 * @return True if the memory was freed, false if an error occured
 */
extern bool free_tokens(char **tokens);


#endif /* GLOB_FUNC_H_ */
