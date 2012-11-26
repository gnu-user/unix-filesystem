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
 * @brief The superblock contains information pertainent to the disk.
 *
 * @details This struct defines the data which will be stored inside the
 * super block. In particular, the super block contains information
 * pertaining to disk attributes, and links to critical file system
 * data structures.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
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
 * @brief Get a handle to the super block.
 *
 * @details This function implements a pseudo-object oriented
 * method for accessing the super block data. It returns
 * the super block as a pointer to a struct, whose individual
 * members can be accessed.
 *
 * @return Returns a pointer to the super block data.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern superblock* get_super_block(void);


/**
 * @brief Get the location of the root directory.
 *
 * @details This function is an accessor method for the
 * pseudo-object attribute inside the super block which
 * contains the location of the root directory's inode
 * on disk.
 *
 * @return Returns the location of root directory on disk.
 * If a failure occurs, return 0.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_root(void);


/**
 * @brief Get the location of the free block list's first index block.
 *
 * @details This function is an accessor method for the
 * pseudo-object attribute inside the super block which
 * contains the location of the free block list structure's
 * first index block on disk.
 *
 * @return Returns the location of the free block list's index block.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_free_block_index(void);


/**
 * @brief Calculate the unique identifier for the super block.
 *
 * @return if the uuid was successfully calculated:
 * if return 1 for successful
 * otherwise unsuccessful
 *
 * @deprecated This function is no longer used, as an external
 * library for unique identifiers has been implemented and used
 * instead. This function was moved to mount.c also, to
 * provide better encapsulation for the function.
 */
//extern int calc_uuid();


/**
 * @brief Validate the unique identifier for the super block.
 *
 * @return an integer value
 * if value >= 1
 * otherwise unsuccessful
 *
 * @deprecated This function is no londer used, as an external
 * library for unique identifiers has been implemented and used
 * instead. This function was moved to mount.c also, to
 * provide better encapsulation for the function.
 */
//extern int validate_uuid();

#endif /* SUPER_BLOCK_H_ */
