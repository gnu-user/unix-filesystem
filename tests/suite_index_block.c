/*
 * suite_index_block.c
 *
 *  Created on: Nov 23, 2012
 *      Author: ubuntu
 */

#include "suite_index_block.h"
#include "unit_tests.h"
#include "../src/glob_data.h"
#include "../src/index_block.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint32_t ROOT;
uint32_t FBL_TOTAL_SIZE;
/**
 * generate_index test case
 */
int test_generate_index(void) {
	/* Test 1 -- generate an index for a single block */

	//wipe the disk and reinitialize
	sfs_initialize(1);

	data_index testindex = generate_index(1);

	/**
	 * The newly generated index should be in the block
	 * after ROOT's index, which is empty because
	 * we just initialized.
	 *
	 * The only index inside that block should be in
	 * the block immediately afterward.
	 *
	 * There should be no more indexes afterward,
	 * so the rest should be null terminated.
	 */
	if ((testindex.index_location != ROOT + 2)
			|| (testindex.data_locations[0] != ROOT + 3)
			|| (testindex.data_locations[1] != NULL )) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	/* Test 2 -- generate an index for an amount
	 * of blocks that require >1 index blocks (in this case, 2) */

	//wipe the disk and reinitialize
	sfs_initialize(1);

	//This should give us 2 locations in the 2nd index block.
	data_index testindex2 = generate_index(1 + ceil(BLKSIZE / sizeof(uint32_t)));

	/**
	 * The newly generated index should be in the block
	 * after ROOT's index, which is empty because
	 * we just initialized.
	 *
	 * There should be (BLKSIZE + 2) indexes in here, because we
	 * generated an index for something which is huge, so the number of
	 * locations indexed should span two index blocks.
	 *
	 * There should be no more indexes afterward,
	 * so the rest should be null.
	 */
	int i = 0;
	for (i = 0; i < (1+floor(BLKSIZE / sizeof(uint32_t))); i++) {
		if (i % (int)((floor(BLKSIZE/sizeof(uint32_t))) - 1 ))
		{
			i++;
		}
		if (testindex2.data_locations[i] != ROOT + i + 3) {
			test_fail("Unit Test Part 1");
			return EXIT_FAILURE;
		}
	}
	//Check null termination.
	i++;
	if (testindex2.data_locations[i] != NULL ) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}

	/**
	 * Manually verify that Index block is written at location 8 and location 40
	 * and check the contents.
	 */

	test_pass("Unit Test Part 1");
	return EXIT_SUCCESS;
}

/**
 * iterate_index test case
 */
int test_iterate_index(void) {
	/* Test 1 -- generate a test index for 5 blocks and
	 * iterate it into memory */

	//wipe the disk and reinitialize
	sfs_initialize(1);

	data_index testindex = generate_index(5);
	locations test = iterate_index(testindex.index_location, NULL );

	int i = 0;
	for (i = 0; i < 5; i++) {
		if ((test[i] != ROOT + 2 + i)) {
			test_fail("Unit Test Part 1");
			return EXIT_FAILURE;
		}
	}
	//Check null termination.
	i++;
	if (test[i] != NULL) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}

	test_pass("Unit Test Part 1");
	return EXIT_SUCCESS;
}

/**
 * calc_index_blocks test case
 */
int test_calc_index_blocks(void) {
	/* Test 1 -- */
	if (0) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	return EXIT_SUCCESS;
}

