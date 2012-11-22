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

//TODO ALL OF THESE HAVE TO BE NULL TERMINATED!!!!!!!!!!
typedef uint32_t* free_locations;
typedef uint32_t* used_locations;

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
 * Gets the free block list independently from where it is located, if the free
 * block list does not already exist in memory (file system has just started) it
 * will read the free block list from disk and set the static instance of the
 * free block list in memory, then return the pointer to that instance in memory,
 * if an error occurs a NULL pointer is returned.
 *
 * @param current_fbl Takes a pointer to the current FBL's static instance in memory.
 * @return The pointer to the static instance of free block list in memory, NULL
 * if an error occurred.
 */
extern free_block_list* get_free_block_list(free_block_list* current_fbl);


/**
 * Finds all of the free blocks that exist in the static instance of the free block list
 * in memory and returns them as a free locations.
 *
 * Used to calculate the total amount of available disk space
 *
 * @return An array containing all of the free locations
 */
extern free_locations calc_total_free_blocks(void);


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
extern free_locations calc_num_free_blocks(uint32_t num_blocks);


/**
 * Finds the next free block in the static free block list (fbl), marks it as used in the
 * fbl and returns the location of the block.
 *
 * get_free_block calculates a single free block and then marks that block as used
 * in the fbl, it essentially operates as a facade for calc_free_blocks and update_fbl when
 * you only want to get one block at a time
 *
 * @return The location of a free block
 *
 */
extern uint32_t get_free_block(void);


/**
 * Writes the static free block list in memory to disk, it essentially syncs the
 * fbl in memory with the instance on disk.
 *
 * After the new FBL is written to disk, a journal entry is created, which links the
 * superblock to the new FBL.
 *
 * @return True if the free block list was successfully written to disk, false
 * otherwise
 */
extern bool write_fbl(free_block_list* current_fbl);


/**
 * Read the FBL from disk using the index either provided by the superblock or the
 * index provided by the FBL entry in the journal[0].arg1 and loads the FBL by
 * iterating through each location within its index and concatenating them all into
 * one buffer, which then overwrites the current static fbl in memory.
 *
 * @param location The location of the fbl's index block on disk
 *
 */
static free_block_list* read_fbl(uint32_t location);


/**
 * Determine what blocks the FBL uses and return all of them as an array (used locations).
 *
 * TODO REMOVE THIS, IT IS ONLY IN THE NON-INDEXED VERSIONS OF FBLS, WE NOW CALL GENERATE
 * INDEX TO CREATE INDICES FOR A NEW INSTANCE OF AN FBL ON THE DISK
 */
//static used_locations index_fbl_blocks(uint32_t index);


/**
 *
 * TODO ADD A NOTE THAT THIS IS CALLED INTERNALLY BY READ_FBL WHEN READING THE FBL FROM DISK
 * TODO THIS IS LITERALLY A WRAPPER FOR ITERATE INDEX THAT CHANGES THE RETURN TYPE TO TYPE FREE_BLOCk_LIST
 *
 * Iterates through the free_block_list index block, concatenates the blocks, and
 * returns a pointer to a buffer containing the entire free_block_list.
 *
 * @param location The location of the index for the free_block_list
 *
 */
static free_block_list* iterate_fbl(uint32_t location);


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
 */
free_block_list* update_fbl(used_locations used,
							free_locations free);


#endif /* FREE_BLOCK_LIST_H_ */
