/*
 * free_block_list.h
 *
 *  Created on: Nov 16, 2012
 *      Author: jon
 */
#include "glob_data.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef FREE_BLOCK_LIST_H_
#define FREE_BLOCK_LIST_H_

/**
 * Containing an array of the locations of free blocks and used blocks. These are used
 * to update the entries in the FBL, and are convenience definitions for use
 * in update_fbl. These can never be bigger than the number of blocks on disk.
 */
typedef uint32_t free_location;

//TODO ALL OF THESE HAVE TO BE NULL TERMINATED!!!!!!!!!!
typedef uint32_t* free_locations;
typedef uint32_t* used_locations;

/**
 * The free_block_list is an array containing the free blocks on disk.
 * Elements are marked as free (false), or used (true).
 * The superblock always points to the index node of the free_block_list.
 */
typedef bool free_block_list[NUMBLKS];

static free_block_list fbl;

/**
 * @return the pointer to the free block list
 */
free_block_list get_free_block(void);

/**
 * Finds free blocks that exist on the given free block list and
 * returns them as a free locations.
 */
free_locations calc_free_blocks(free_block_list fbl);


/**
 * Finds the specified number of free blocks on the given free block list,
 * and returns them if there are enough free.
 */
free_locations calc_num_free_blocks(free_block_list fbl, uint32_t num_blocks);


/**
 * Finds the next free block on the specified free block list (fbl), marks it as used on the fbl,
 * and returns the location of the block.
 *
 * get_free_block calculates a single free block and then marks that block as used
 * in the fbl, it essentially operates as a wrapper for calc_free_blocks and update_fbl
 *
 */
free_location get_free_block(free_block_list fbl);


/**
 * Writes the free block list to disk.
 *
 * After the new FBL is written to disk, a journal entry is created and
 * journalled, which links the superblock to the new FBL.
 */
extern int write_fbl(free_block_list fbl);


/**
 * Read the FBL from disk using the index either provided by the superblock or the
 * index provided by the FBL entry in the journal[0].arg1 and load the FBL by
 * iterating through each node and concatenating them all within one buffer.
 */
static free_block_list* read_fbl(free_block_list fbl, uint32_t index);


/**
 * Determine what blocks the FBL uses and return all of them as an array (used locations).
 */
static used_locations index_fbl_blocks(uint32_t index);


/**
 * Iterates through the free_block_list index block, concatenates the blocks, and
 * returns a pointer to a buffer containing the entire free_block_list.
 * @param index The index of the free_block_list index block
 *
 */
static free_block_list* iterate_fbl(uint32_t index);


/**
 * The update FBL method updates the FBL entry in memory. It will take
 * the FBL buffer in memory as the first argument, an array of all the locations
 * to mark as used as the second argument, and an array of all the locations to mark
 * as unused as the third argument. If the arguments used or free are NULL then no blocks
 * are marked for that type.
 *
 * @pre parameters used, free MUST be NULL terminated arrays of locations
 *
 * @param used A NULL terminated array of locations to mark as used in the fbl, if it is NULL
 * then no locations are marked as used
 * @param free A NULL terminated array of locations to mark as free in the fbl, if it is NULL
 * then no locations are marked as free
 *
 */
free_block_list* update_fbl(free_block_list fbl,
							used_locations used,
							free_locations free);


#endif /* FREE_BLOCK_LIST_H_ */
