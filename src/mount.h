#include "glob_data.h"
#include "super_block.h"

#ifndef MOUNT_H_
#define MOUNT_H_

extern int mount(void);
extern int validate_super_block(void);

//Use check_journal()
//To validate_free_block_list

extern int validate_root_dir(void);

#endif /* MOUNT_H_ */
