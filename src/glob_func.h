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
 * TODO UPDATE CONCAT TO TAKE A DOUBLE POINTER FOR DEST BECAUSE REALLOC MAY ACTUALLY
 * SET DEST TO A DIFFERENT POINTER ADDRESS, THE PARENT NEEDS TO BE UPDATED....
 *
 * TODO WRITE UNIT TEST & TEST FUNCTION
 *
 * Concatenates two arrays, a dest and a src array into a single array
 * containing the contents of both arrays, the terminating null character in
 * dest is overwritten by the first character of src, and a NULL character
 * is included at the end of the new array. A pointer dest containing the resulting
 * array containing the contents of both arrays is then returned.
 *
 * TODO Should this free the src or let the person who called it handle that
 * is there ever a case where you still want to use the two items after concat???
 *
 * @note the function automatically frees the memory for the src array after 
 * successfully copying the contents of both into the resulting new array
 *
 * @pre The function is UNDEFINED if the destination or source pointer are NULL
 * if either is NULL they are not used and NULL is simply returned
 * @pre The arrays dest and source must contain the same data type
 *
 * @param dest double pointer to a NULL terminated array, dest is passed by reference
 * @param source pointer to a NULL terminated array
 * @param size The size in bytes of each item in the array
 *
 * @return A pointer to the resulting array containing the concatenated results
 *
 */
extern void* concat(void** dest, void* src, uint32_t size);


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
