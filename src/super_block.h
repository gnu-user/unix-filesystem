/**
 * The structures used for the super_block component of the file system:
 *
 * (Integer) Size of disk (in blocks), which will take up 4 bytes of the block,
 * (Integer) Block size (in bytes), which will take up 4 bytes of the block,
 * A Pointer to the free block linked list, which will take 8 bytes,
 * A Pointer to the Inode table for the root directory, which will take 8 bytes,
 * (Integer) A Device id, which will take up 4 bytes.
*/
#include "glob_func.h"
#include "error.h"

#ifndef SUPER_BLOCK_H_
#define SUPER_BLOCK_H_

/**
 * @struct Superblock
 *
 * This struct defines the data which will be stored inside the
 * super block. In particular, the super block contains information
 * pertaining to disk attributes, and links to critical file system
 * data structures.
 */
typedef struct
{
	uint32_t size_of_disk;		/** Total number of blocks on the disk. */
	uint32_t block_size;		/** Block size of the disk, in bytes per block.  */
	uint32_t free_block_list;	/** Location of the free block list data structure on disk. */
	uint32_t root_dir;			/** Location of the root directory's inode on disk. */
	uint32_t device_id;			/** @deprecated Device identifier for the disk. No longer required since UUID was implemented. */
	uuid_t uuid;				/** Universal unique identifier for the disk. */
} superblock;

/**
 * Get a handle to the super block.
 *
 * @return Returns a pointer to the super block data.
 */
extern superblock* get_super_block(void);

/**
 * Get the location of the root directory.
 *
 * @return Returns the location of root directory on disk. If a failure occurs, return 0.
 */
extern uint32_t get_root(void);

/**
 * Get the location of the free block list's first index block.
 *
 * @return The location of the free block list's index block.
 */
extern uint32_t get_free_block_index(void);

/**
 * Calculate the uuid for the super block.
 *
 * @return if the uuid was successfully calculated:
 * if return 1 for successful
 * otherwise unsuccessful
 * TODO remove, unnecessary
 */
//extern int calc_uuid();

/**
 * Validate the uuid
 *
 * @return an integer value
 * if value >= 1
 * otherwise unsuccessful
 * TODO remove, Already in the mount.c
 */
//extern int validate_uuid();

#endif /* SUPER_BLOCK_H_ */
