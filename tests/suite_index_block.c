/*
 * suite_index_block.c
 *
 *  Created on: Nov 23, 2012
 *      Author: ubuntu
 */

#include "suite_index_block.h"
#include "unit_tests.h"
#include "../src/glob_data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * generate_index test case
 */
int test_generate_index(void) {
	/* Test 1 -- generate an index for a single block */

	//TODO initialize the file system here

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
	 * so the rest should be null
	 */
	if ((testindex.index_location != ROOT + 2) ||
			(testindex.data_locations[0] != ROOT + 3) ||
			(testindex.data_locations[1] != NULL)) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	return EXIT_SUCCESS;
}

/**
 * iterate_index test case
 */
int test_iterate_index(void) {
	/* Test 1 -- */
	if (0) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

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

