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
#include "../lib/uuid/uuid.h"
#include "error.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef GLOB_FUNC_H_
#define GLOB_FUNC_H_


/**
 * @brief Allocate a buffer to write to memory of a given size.
 *
 * @param buf The buffer to allocate the space for.
 *
 * @param size The size for the new buffer's elements.
 *
 * @return Returns a pointer to the new buffer.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern byte* allocate_buf(byte* buf, uint32_t size);


/**
 * @brief Copy the data from one buffer to another, given the size of both.
 *
 * @param buf1 The buffer to copy from.
 *
 * @param buf2 The buffer to copy to.
 *
 * @param size1 The size of the buffer to copy from.
 *
 * @param size2 The size of the buffer to copy to.
 *
 * @return Returns the second buffer with the contents of the
 * first buffer inside.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern byte* copy_to_buf(byte* buf1, byte* buf2, uint32_t size1, uint32_t size2);


/**
 * @brief Calculate the number of bytes in a byte buffer.
 *
 * @pre The buf parameter must be NULL terminated.
 *
 * @param buf A NULL terminated buffer.
 *
 * @return Returns the number of bytes inside the buffer,
 * up to the NULL terminator.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t calc_num_bytes(byte* buf);


/**
 * @brief Calculates the number of blocks needed to store data.
 *
 * @details Helper function which calculates the number of blocks
 * needed to store the data, if an error occurs 0 is returned.
 * Reads up to MAX_IO_LENGTH + 1, if the buffer is still not terminated
 * then the IO buffer is larger than the maximum specified by the file
 * system, an error occurs and 0 is returned.
 *
 * @pre The buf parameter must be NULL terminated.
 *
 * @param buf A NULL terminated buffer.
 *
 * @return Returns the number of blocks needed to store the given data.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t calc_num_blocks(byte* buf);


/**
 * @brief Concatenate two arrays.
 *
 * @details Concatenates two NULL termianted arrays, a src_1 and a src_2 array into a
 * single NULL terminated array containing the contents of both arrays. The
 * terminating NULL character in src_1 is overwritten by the first character of
 * src_2, and a NULL character is included at the end of the new array. A pointer
 * to the resulting array containing the contents of both arrays is then returned.
 *
 * @pre The arrays src_1 and src_2 MUST BE NULL TERMINATED.
 *
 * @pre The arrays to concatenate MUST contain the same data type for the concatenation
 * to function properly.
 *
 * @param src_1 A pointer to a NULL terminated array.
 *
 * @param src_2 A pointer to a NULL terminated array.
 *
 * @param size The size in bytes of each item in the array.
 *
 * @return Returns a pointer to the resulting array containing
 * the concatenated results.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern void* concat(void* src_1, void* src_2, uint32_t size);


/**
 * @brief Concatenate two byte arrays.
 *
 * @details Concatenates a specified number of bytes from src_2 to src_1, into a
 * single NULL terminated array containing the contents of both arrays. The
 * difference is that when performing concatenation it concatenates a specified
 * number of bytes from src_2 to src_1. The terminating NULL character in src_1
 * is overwritten by the first character of src_2, and a NULL character is
 * included at the end of the new array. A pointer to the resulting array
 * containing the contents of both arrays is then returned.
 *
 * @pre The array src_1 MUST BE NULL TERMINATED.
 *
 * @pre The arrays to concatenate MUST contain the same data type for the concatenation
 * to function properly.
 *
 * @pre The specified length, must be <= the length of src_2.
 *
 * @param src_1 A pointer to a NULL terminated array.
 *
 * @param src_2 A pointer to an array.
 *
 * @param size The size in bytes of each item in the array.
 *
 * @param len The length in BYTES of the data to concatenate from src_2 to src_1.
 *
 * @return Returns a pointer to the resulting array containing
 * the concatenated results.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern void* concat_len(void* src_1, void* src_2, uint32_t size, uint32_t len);


/**
 * @brief Tokenize a path into an array of tokens.
 *
 * @details Tokenizes the path provided into an array of tokens for
 * each component in the path and returns an array to a null terminated
 * array of tokens. For example using pathname = "/foo/bar" the resulting
 * tokens array would be: *
 * [0]	=>	"foo"
 * [1]	=>	"bar"
 * [2]	=>	NULL
 * If an error occurs a NULL pointer will be returned.
 * Tokens are each a string, therefore the resultant pointer will point to
 * a two-dimensional array of characters.
 *
 * @pre Each component in the pathname must be at most (including the NULL
 * termination) MAX_NAME_LEN otherwise an error occurs, and a NULL
 * pointer returned.
 *
 * @param pathname The pathname to tokenize.
 *
 * @return Returns a pointer to the 2D tokens array.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern char** tokenize_path(char* pathname);


/**
 * @brief Ensure a specified pathname is valid.
 *
 * @details This is a static function used by tokenize_path to verify
 * that the pathname is valid before tokenizing. It returns true if the
 * path is valid, and returns false if there are errors in the pathname.
 *
 * @param pathname The pathname to validate.
 *
 * @return Returns true if the path is valid, false if path is invalid.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
static bool validate_path(char* pathname);


/**
 * @brief Determine whether individual path tokens are valid.
 *
 * @details This is a static function used by tokenize_path to verify
 * that the pathname components are valid. It returns true if the path
 * is valid, and returns false if there are errors in the pathname.
 *
 * @param tokens The 2D tokens array to validate.
 *
 * @return Returns true if the tokens are valid, false if
 * tokens are invalid.
 *
 */
static bool validate_tokens(char** tokens);


/**
 * @brief Frees the memory allocated for the tokens.
 *
 * @details This function is used to free memory used by dynamic memory
 * allocation methods required for two dimensional string manipulation,
 * preventing memory leaks.
 *
 * @param tokens The NULL terminated 2D array filled with tokens to be freed.
 *
 * @return Returns true if the memory was freed, false if an error occurred.
 */
extern bool free_tokens(char **tokens);


#endif /* GLOB_FUNC_H_ */
