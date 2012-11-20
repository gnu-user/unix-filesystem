/*
 * suite_glob_func.h
 *
 *  Created on: Nov 20, 2012
 *      Author: dsmullen
 */
#include "suite_blockio.h"
#include "unit_tests.h"
#include "../src/glob_data.h"
#include <stdlib.h>

/*
 * get_block test cases
 *
 */
int test_get_block(void) {
	byte temp[128] = { 0 };
	int blknum;

	/* Test 1 -- get_block with a block that exists */
	blknum = 5;
	if (get_block(blknum, temp) != 0) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	/* Test 2 -- get_block with a block that is below the 0th index */
	blknum = -5;
	if (get_block(blknum, temp) == 0) {
		test_fail("Unit Test Part 2");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 2");
	}

	/* Test 3 -- get_block with a block that is above the largest index */
	blknum = NUMBLKS + 1;
	if (get_block(blknum, temp) == 0) {
		test_fail("Unit Test Part 3");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 3");
	}

	return EXIT_SUCCESS;
}

/*
 * put_block test cases
 *
 */
int test_put_block(void) {
	byte temp[128] = { 1 };
	int blknum;

	/* Test 1 -- put_block with a block that exists */
	blknum = 5;
	if (put_block(blknum, temp) != 0) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	/* Test 2 -- put_block with a block that is below the 0th index */
	blknum = -5;
	if (put_block(blknum, temp) == 0) {
		test_fail("Unit Test Part 2");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 2");
	}

	/* Test 3 -- put_block with a block that is above the largest index */
	blknum = NUMBLKS + 1;
	if (put_block(blknum, temp) == 0) {
		test_fail("Unit Test Part 3");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 3");
	}

	return EXIT_SUCCESS;
}
