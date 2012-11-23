/*
 * initialize.h
 *
 *  Created on: Nov 22, 2012
 *      Author: jon
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_


/**
 * Initialize the superblock for the file system.
 * @param erase integer, Determines whether or not to delete the contents of the
 * file system
 * If this value is 1 then it will erase every block on the disk and then
 * re-create the super block, free block list blocks and the root directory.
 * If the value is 0 then it will re-create the super block, the free block
 * list blocks and the root directory.
 *
 * @return an integer value,
 * If the value > 0 then the initialization was successful
 * If the value <= 0 then the initialization failed
 */
extern int sfs_initialize(int erase);


/**
 * Allocate all of the blocks to the free block list
 *
 * @return a integer value
 * if the free block init fails the value will be -1
 * otherwise it will be 0
 */
extern int free_block_init(void);


/**
 * Wipes the drive block by block
 *
 * @return a integer value
 * if the free block init fails the value will be -1
 * otherwise it will be 0
 */
extern int wipe_disk(void);


#endif /* INITIALIZE_H_ */
