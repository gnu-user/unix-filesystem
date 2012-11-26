#include "I_node.h"
#include "../lib/uuid/uuid.h"
#include "error.h"
#include <string.h>

#ifndef SYSTEM_OPEN_FILE_TABLE_H_
#define SYSTEM_OPEN_FILE_TABLE_H_


/**
 * @struct swoft
 *
 * @brief Pseudo-object containing the array of open file descriptors.
 *
 * @details The system wide open file table contains an array of
 * file descriptors, which are locations of inodes that have been
 * read from the disk into memory. These are used as handles to
 * the files which exist on disk, and are synchronized with the
 * data on disk upon modification. One instance needs to exist per file.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
typedef struct{
	uint32_t fd[NUMOFL];
	bool taken[NUMOFL];
} swoft;


/**
 * @var system_open_tb
 *
 * @brief The static instance of the system wide open file table.
 *
 * @details This variable holds the singleton instance of the
 * system wide open file table. It represents an instance of a
 * pseudo-object which can only be accessed and modified through
 * the accessor and mutator methods provided.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern swoft system_open_tb;


/**
 * @brief Add the inode to the system wide open file table.
 *
 * @details This function takes an inode's block location
 * on disk, reads that block, and assigns the returned inode
 * location on disk into memory to a file descriptor - this is
 * an index on the system wide open file table.
 *
 * @param block_num The inode's location on disk.
 *
 * @return Returns an integer value, if the value >= 0 then
 * the inode was found and added to the system wide open
 * file table. If the value = -1 then the table was full.
 * If the value = -2 then the inode was not found.
 * By default, any other return value signals that the
 * function was unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int add_to_swoft(uint32_t block_num);


/**
 * @brief Validate whether the given file descriptor is
 * a valid file descriptor in the system wide open file
 * table.
 *
 * @param fd The file descriptor.
 *
 * @return Returns an integer value, if the value >= 0
 * the file descriptor was valid, otherwise the file
 * descriptor was invalid, or the function was
 * unsuccessful.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern int validate_fd(int fd);


/**
 * @brief Get an inode instance from the system wide open
 * file table.
 *
 * @details This function takes a file descriptor, which is
 * an index on the system wide open file table. If there is
 * an inode pseudo-object at the index specified, it is
 * returned.
 *
 * @param fd The file descriptor.
 *
 * @return Returns the inode instance from the system
 * wide open file table given the file descriptor.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern inode get_swoft_inode(int fd);


/**
 * @brief Get the location of the inode on
 * disk which corresponds to a file descriptor.
 *
 * @details This function takes a file descriptor, and
 * if there is a valid inode pseudo-object at that index
 * on the system wide open file table, the location of
 * that object on disk is returned from accessing
 * it within the pseudo-object.
 *
 * @param fd The file descriptor.
 *
 * @return Returns the location of the inode on disk.
 *
 * @author Daniel Smullen
 *
 * @author Jonathan Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t get_inode_loc(int fd);


/**
 * @brief Remove a file descriptor from the system wide open
 * file table.
 *
 * @details This function accesses an index on the system
 * wide open file table, and frees whatever data is in
 * memory corresponding to that index.
 *
 * @param fd The file descriptor to remove.
 */
extern void remove_fd(int fd);


/**
 * @brief Find all the system wide open file table indices that have
 * the same data as the given location on disk, and remove them from
 * the system wide open file table.
 *
 * @details This function is used when deleting files. In order to
 * remove all open handles to a file when it is removed from disk,
 * the system wide open file table must have all corresponding
 * handles removed.
 *
 * @param inode_location The location of the inode on disk.
 *
 * @return Returns an integer value indicating the number of
 * entries deleted from the system wide open file table.
 */
extern uint32_t find_and_remove(uint32_t inode_location);


#endif /* SYSTEM_OPEN_FILE_TABLE_H_ */
