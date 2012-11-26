/*
 * free_block_list.h
 *
 *  Created on: Nov 16, 2012
 *      Author: jon
 */
#include "glob_data.h"
#include "error.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef FREE_BLOCK_LIST_H_
#define FREE_BLOCK_LIST_H_

/**
 * Containing an array of the locations of free blocks and used blocks. These are used
 * to update the entries in the FBL, and are convenience definitions for use
 * in update_fbl. These can never be bigger than the number of blocks on disk.
 */


/**
 * The free_block_list is an array containing the free blocks on disk.
 * Elements are marked as free (false), or used (true).
 * The superblock always points to the index node of the free_block_list.
 */
typedef struct
{
	bool free_blocks[NUMBLKS];
} free_block_list;

static free_block_list fbl;


/**
 * Gets the free block list independently from where it is located. If the free
 * block list does not already exist in memory (file system has just started) it
 * will read the free block list from disk using the index provided by the superblock
 * and set the static instance of the free block list in memory. Then, return the
 * pointer to the static instance in memory. If an error occurs,
 * a NULL pointer is returned.
 *
 * @return A pointer to the static instance of free block list in memory, NULL
 * if an error occurred.
 */
extern free_block_list* get_free_block_list(void);


/**
 * Finds all of the free blocks that exist in the static instance of the free block list
 * in memory and returns them as a free locations.
 *
 * Used to calculate the total amount of available disk space
 *
 * @return An array containing all of the free locations
 */
extern locations calc_total_free_blocks(void);


/**
 * Finds the specified number of free blocks in the static instance of the free block
 * list in memory. It returns NULL if there are not enough free blocks, otherwise it
 * returns an array of the free locations.
 *
 * Used to calculate whether there is enough disk space before starting to create the
 * file
 *
 * @param num_blocks The number of free blocks needed
 * @return An array of the free locations, or NULL if there are not enough free blocks
 *
 */
extern locations calc_num_free_blocks(uint32_t num_blocks);


/**
 * Finds the next free block in the static free block list (fbl), marks it as used in the
 * fbl and returns the location of the block.
 *
 * get_free_block calculates a single free block and then marks that block as used
 * in the fbl, it essentially operates as a facade for calc_free_blocks and update_fbl when
 * you only want to get one block at a time
 *
 * If there are no free blocks available, it will return 0 (the superblock's location),
 * which is always used by the superblock.
 *
 * @return The location of a free block. Return 0 if no free blocks available.
 *
 */
extern uint32_t get_free_block(void);


/**
 * The update FBL method updates the static FBL entry in memory. It will take
 * an array of all the locations to mark as used as the first argument, and an
 * array of all the locations to mark as unused as the second argument. If the
 * arguments used or free are NULL then no blocks are marked for that type.
 *
 * @pre parameters used and free MUST be NULL terminated arrays of locations
 *
 * @param used A NULL terminated array of locations to mark as used in the fbl,
 * if it is NULL then no locations are marked as used
 * @param free A NULL terminated array of locations to mark as free in the fbl,
 * if it is NULL then no locations are marked as free
 *
 * @return A pointer to the static instance of free block list in memory, NULL
 * if an error occurred
 */
extern free_block_list* update_fbl(locations used, locations free);


/**
 * Writes the static free block list in memory to disk. This synchronizes the
 * static free block list in memory with the contents on disk, making the
 * current state of the free blocks on disk permanent.
 *
 * @return A pointer to the static instance of free block list in memory, NULL
 * if an error occurred synchronizing the free block list to disk.
 */
extern free_block_list* sync_fbl(void);


/**
 * Resets the free block list in memory by loading the free blocks list from
 * disk and overwriting the static instance of the free block list in memory.
 * This function is used to refresh the state of the free block list in memory
 * if an error occurs.
 *
 * @return A pointer to the static instance of free block list in memory, NULL
 * if an error occurred
 */
extern free_block_list* reset_fbl(void);

#endif /* FREE_BLOCK_LIST_H_ */
