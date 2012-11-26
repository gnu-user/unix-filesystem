/*
 * initialize.h
 *
 *  Created on: Nov 22, 2012
 *      Author: jon
 */

#include "error.h"

#ifndef INITIALIZE_H_
#define INITIALIZE_H_


/**
 * @brief Initialize the superblock for the file system.
 *
 * @param erase Determines whether or not to delete the contents of the
 * file system. If this value is 1 then it will erase every block on the
 * disk and then re-create the super block, free block list data structure
 * and the root directory. If the value is 0 then it will re-create
 * the super block, the free block list blocks and the root directory.
 *
 * @return Returns an integer value, if the value > 0 then the
 * initialization was successful. If the value <= 0 then
 * the initialization failed.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int sfs_initialize(int erase);


/**
 * @brief Allocate all of the blocks in the free block list.
 *
 * @details This function initializes the free block list data
 * structure for the first time. This is used only when the disk
 * is being reinitialized. In effect, writing all NULL values to
 * this data structure (save for the superblock) marks all values
 * on the disk free to be written on.
 *
 * @return Returns an integer value, if the free block list
 * initialization fails the value will be -1. Otherwise,
 * it will be 0.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int free_block_init(void);


/**
 * @brief Wipes the drive block by block.
 *
 * @details This function ensures that every block on the disk
 * is initialized to zero. Failing to wipe the disk when the
 * file system is reinitialized will result in having garbage
 * data residing in all the blocks that have not yet been written
 * to. These blocks are marked as free in the free block list
 * structure regardless, so they are simple overwritten and the
 * data inside is ignored. This is analogous to a "quick format"
 * command.
 *
 * @return Returns an integer value. If the wipe fails the value
 * will be -1, otherwise it will be 0.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int wipe_disk(void);


#endif /* INITIALIZE_H_ */
