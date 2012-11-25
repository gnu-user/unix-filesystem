#include "glob_data.h"
#include "super_block.h"

#ifndef MOUNT_H_
#define MOUNT_H_

/**
 * Call validate methods to ensure that the mount is possible,
 * and filesystem isn't corrupted.
 *
 * @return an integer value,
 * if value = 1 pass
 * if value = -1 fail
 */
extern int mount(void);

/**
 * Validate the superblock is on the hard drive
 *
 * @return an integer value,
 * if value = 1 pass
 * if value = -1 fail
 */
extern int validate_super_block(void);

//Use check_journal()
//To validate_free_block_list

/**
 * Validate that there is a root directory on the hard drive
 * TODO fix seg fault error if the root directory was not written/was over
 * written
 *
 * @return an integer value,
 * if value = 1 pass
 * if value = -1 fail
 */
extern int validate_root_dir(void);

#endif /* MOUNT_H_ */
