/*
 * glob_func.h
 *
 * Contains an aggregate collection of globally accessible functions
 *
 */
#include "glob_data.h"
#include <stdint.h>
#include <stdio.h>

#ifndef GLOB_FUNC_H_
#define GLOB_FUNC_H_

extern byte write_buffer[BLKSIZE];

extern byte read_buffer[BLKSIZE];

extern byte* allocate_buf(byte* buf, uint32_t size);

extern byte* copy_to_buf(byte* buf1, byte* buf2, uint32_t size1, uint32_t size2);

/**
 * Concatenates two arrays, a dest and a src array into a single array
 * containing the contents of both arrays, the terminating null character in
 * dest is overwritten by the first character of src, and a NULL character
 * is included at the end of the new array. A pointer to the resulting array
 * containing the contents of both arrays is then returned.
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
 * @param dest pointer to a NULL terminated array
 * @param source pointer to a NULL terminated array
 * @param size The size in bytes of each item in the array
 *
 * @return A pointer to the resulting array containing the concatenated results
 *
 */
extern void* concat(void* dest, void* src, uint32_t size);

#endif /* GLOB_FUNC_H_ */
