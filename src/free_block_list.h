/*
 * free_block_list.h
 *
 *  Created on: Nov 16, 2012
 *      Author: jon
 */
#include "globdata.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef FREE_BLOCK_LIST_H_
#define FREE_BLOCK_LIST_H_


/**
 * Indices containing the indexes of free blocks and used blocks. These are used
 * to update the entries in the FBL, and are convenience definitions for use
 * in update_fbl. These can never be bigger than the number of blocks on disk.
 */
uint32_t free_indices[NUMBLKS];
uint32_t used_indices[NUMBLKS];


/**
 * The free_block_list is an array containing the free blocks on disk.
 * Elements are marked as free (false), or used (true).
 * The superblock always points to the index node of the free_block_list.
 */
bool free_block_list[BLKSIZE];

/**
 * Finds free blocks that exist on the given free block list and
 * returns them as a free_indices.
 */
free_indices calc_free_blocks(free_block_list* fbl);

/**
 * Writes the free block list to disk. The free block list contains an index at
 * the end of each block in the list which links to the next block. If there is
 * no index at the end of the block, it is the last block.
 *
 * After the new FBL is written to disk, a journal entry is created and
 * journalled, which links the superblock to the new FBL.
 */
write_fbl(char * buf);

/**
 * Read the FBL from disk using the index either provided by the superblock or the
 * index provided by the FBL entry in the journal[0].arg1 and load the FBL by
 * iterating through each node and concatenating them all within one buffer.
 */
free_block_list* read_fbl(free_block_list* fbl, uint32_t index);
/*
    --> Calls the iterate_fbl which iterates through the nodes in the
        free_block_list linked list
*/

/**
 * Iterates through the free_block_list index block, concatenates the blocks, and
 * returns a pointer to a buffer containing the entire free_block_list.
 * @param index The index of the free_block_list index block
 *
 */
static free_block_list* iterate_fbl(uint32_t index);

/**
 * The update FBL method updates the FBL entry in memory. It will take
 * the FBL buffer in memory as the first argument, an array of all the indexes
 * to mark as used as the second argument, and an array of all the indexes to mark
 * as unused as the third argument.
 */
free_block_list* update_fbl(free_block_list* buf, used_indices someUsedIndices, free_indices someFreeIndices);






#endif /* FREE_BLOCK_LIST_H_ */
