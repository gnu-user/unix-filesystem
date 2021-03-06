/*
 * suite_free_block_list.h
 *
 *  Created on: Nov 21, 2012
 *      Author: ubuntu
 */
#include "../src/error.h"
#include <stdbool.h>

#ifndef SUITE_FREE_BLOCK_LIST_H_
#define SUITE_FREE_BLOCK_LIST_H_

/*
 * write_fbl test case
 */
extern bool test_write_fbl(void);

/*
 * get_free_block_list test case
 */
extern int test_get_free_block_list(void);

/*
 * update_fbl test case
 */
extern int test_update_fbl(void);

/*
 * get_free_block test case
 */
extern int test_get_free_block(void);

#endif /* SUITE_FREE_BLOCK_LIST_H_ */
