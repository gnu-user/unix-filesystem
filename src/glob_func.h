/*
 * glob_func.h
 *
 * Contains an aggregate collection of globally accessible functions
 *
 */
#include "glob_data.h"
#include "../lib/uuid/uuid.h"
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
 * Helper function which calculates the number of blocks needed to store the data,
 * if an error occurs 0 is returned. Reads up to MAX_IO_LENGTH + 1, if the buffer
 * is still not terminated then the IO buffer is larger than specified by the file
 * system, an error occurs and 0 is returned.
 *
 * @pre The buf parameter must be NULL terminated
 * @param buf A NULL terminated buffer
 *
 * @return The number of blocks needed to store the data
 */
extern uint32_t calc_num_blocks(byte* buf);


/**
 * Helper function which calculates the number of blocks needed to store the data,
 * if an error occurs 0 is returned
 *
 * @param size The size of the data in bytes
 *
 * @return The number of blocks needed to store the data
 */


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
 * Concatenates a specified number of bytes from src_2 to src_1, into a
 * single NULL terminated array containing the contents of both arrays. The
 * difference is that when performing concatenation it concatenates a specified
 * number of bytes from src_2 to src_1.
 *
 * The terminating NULL character in src_1 is overwritten by the first character of
 * src_2, and a NULL character is included at the end of the new array. A pointer
 * to the resulting array containing the contents of both arrays is then returned.
 *
 * @pre The arary src_1 MUST BE NULL TERMINATED
 * @pre The arrays to concatenate MUST contain the same data type for the concatenation
 * to function properly
 * @pre The specified len, must be <= the length of src_2
 *
 * @param src_1 A pointer to a NULL terminated array
 * @param src_2 A pointer to an  array
 * @param size The size in bytes of each item in the array
 * @param len The length in BYTES of the data to concatenate from src_2 to src_1
 *
 * @return A pointer to the resulting array containing the concatenated results
 */
extern void* concat_len(void* src_1, void* src_2, uint32_t size, uint32_t len);


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
 * A Static function used by tokenize_path to verify that the pathname is valid before
 * tokenizing, returns true if the path is valid, returns false if there are errors in the
 * pathname.
 *
 * @param pathname The pathname
 *
 * @return True if the path is valid, false if path is invalid
 *
 */
static bool validate_path(char* pathname);


/**
 * A Static function used by tokenize_path to verify that the pathname components are
 * valid, returns true if the path is valid, returns false if there are errors in the
 * pathname.
 *
 * @param tokens The 2D tokens array
 *
 * @return True if the tokens are valid, false if torkens are invalid
 *
 */
static bool validate_tokens(char** tokens);

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
