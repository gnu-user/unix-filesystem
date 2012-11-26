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
 * @struct free_block_list
 *
 * @brief The free_block_list is an array containing the free blocks on disk.
 * Elements are marked as free (false), or used (true). The super block
 * always points to the first index block of the free_block_list.
 */
typedef struct
{
	bool free_blocks[NUMBLKS];		/** Holds a boolean value for each block on the disk, marking whether it is free or used.*/
} free_block_list;

/**
 * @var fbl
 *
 * @brief Holds the static instance of the free block list in memory.
 *
 * @details This variable supports a pseudo-object oriented approach
 * to encapsulating the free block list data structure within the program.
 * Accessor and mutator methods to the free block list are available, and
 * are the only way to access the singleton instance of the data structure.
 */
static free_block_list fbl;


/**
 * @brief Obtains a handle to the free block list static instance, regardless of
 * whether it is available in memory or on disk.
 *
 * @details Gets the free block list independently from where it is located.
 * If the free block list does not already exist in memory (file system has
 * just started) it will read the free block list from disk using the
 * index provided by the super block and set the static instance of
 * the free block list in memory. Then, return the pointer to the
 * static instance in memory. If an error occurs, a NULL pointer is returned.
 *
 * @return A pointer to the static instance of free block list in memory, NULL
 * if an error occurred.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern free_block_list* get_free_block_list(void);


/**
 * @brief Used to calculate the total amount of available disk space.
 *
 * @details Finds all of the free blocks that exist in the static instance
 * of the free block list in memory and returns them as a locations object.
 *
 * @return Returns an array containing all of the free locations.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern locations calc_total_free_blocks(void);


/**
 * @brief Used to calculate whether there is enough disk space before starting to
 * create a file on disk.
 *
 * @details Finds the specified number of free blocks in the static instance
 * of the free block list in memory. It returns NULL if there are not enough
 * free blocks, otherwise it returns an array of the free locations.
 *
 * @param num_blocks The number of free blocks needed.
 *
 * @return Returns an array of the free locations,
 * or NULL if there are not enough free blocks.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern locations calc_num_free_blocks(uint32_t num_blocks);


/**
 * @brief Finds the next free block in the static free block list,
 * marks it as used and returns the location of the block.
 *
 * @details This function finds a single free block and then marks
 * that block as used in the free block list, it essentially operates
 * as a facade for the calc_free_blocks function and the update_fbl function
 * when you only want to get one block at a time. If there are no free
 * blocks available, it will return 0 (the superblock's location),
 * which is always used by the superblock.
 *
 * @return The location of a free block. Return 0 if no free blocks available.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_free_block(void);


/**
 * @brief Accessor method for the free block list static instance in memory.
 *
 * @details The update FBL method updates the static FBL entry in memory.
 * It will take an array of all the locations to mark as used as the
 * first argument, and an array of all the locations to mark as unused
 * as the second argument. If the arguments used or free are NULL then
 * no blocks are marked for that type.
 *
 * @pre Parameters used and free MUST be NULL terminated arrays of locations.
 *
 * @param used A NULL terminated array of locations to mark as used in the
 * free block list, if it is NULL then no locations are marked as used.
 *
 * @param free A NULL terminated array of locations to mark as free
 * in the free block list, if it is NULL then no locations are marked
 * as free.
 *
 * @return Returns a pointer to the static instance of free block list
 * in memory, NULL if an error occurred.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern free_block_list* update_fbl(locations used, locations free);


/**
 * @brief Synchronizes the free block static instance in memory by writing
 * it to disk.
 *
 * @details Writes the static free block list in memory to disk.
 * This synchronizes the static free block list in memory with the contents
 * on disk, making the current state of the free blocks on disk permanent.
 *
 * @return Returns a pointer to the static instance of free block
 * list in memory, NULL if an error occurred synchronizing the free
 * block list to disk.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern free_block_list* sync_fbl(void);


/**
 * @brief Overwrites the free block list in memory with the most recent version on disk.
 *
 * @details Resets the free block list in memory by loading the free blocks list from
 * disk and overwriting the static instance of the free block list in memory.
 * This function is used to refresh the state of the free block list in memory
 * if an error occurs.
 *
 * @return Returns a pointer to the static instance of free block list in memory, NULL
 * if an error occurred.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern free_block_list* reset_fbl(void);


/**
 * @brief Reinitializes the free block list in memory.
 *
 * @details Wipes the contents of the free block list in memory, which sets
 * all of the locations in the free block list in memory as free.
 * This function is used to reset the free block list in memory after
 * initializing a new disk.
 *
 * @return Returns a pointer to the free block list, NULL if an error occurred.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern free_block_list* wipe_fbl(void);


#endif /* FREE_BLOCK_LIST_H_ */
