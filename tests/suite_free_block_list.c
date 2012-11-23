/*
 * suite_free_block_list.c
 *
 *  Created on: Nov 21, 2012
 *      Author: ubuntu
 */

#include "suite_free_block_list.h"
#include "unit_tests.h"
#include "../src/free_block_list.h"
#include "../src/glob_data.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int test_get_free_block_list(void)
{

	//TODO update the contents of this data structure with what's supposed to be in the FBL after initializing the disk
	const free_block_list fbl_test_data =
	{ .free_blocks =
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0 } };

	//TODO initialize the filesystem here

	//TODO this is cheating - change this so that it copies the FBL from the static instance into our local scope
	// Use the pointer returned by get_free_block_list to copy the values of the fbl into a test fbl to compare with
	// the expected results in fbl_test_data
	//memcpy(&fbl, &fbl_test_data, sizeof(free_block_list));

	/**
	 * Test 1 - test whether we can retrieve the fbl from our local static instance
	 */

	if (get_free_block_list() == NULL
			|| memcmp(get_free_block_list(), &fbl_test_data,
					sizeof(free_block_list)) != 0)
	{
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 1");
	}

	/**
	 * Test 2 - test whether we can retrieve the fbl from disk
	 */

	/**
	 * The FBL data that's in memory should reflect the one on disk since we haven't changed anything.
	 * Therefore, free the one in memory so that we can update it again from disk and compare to our test data.
	 */

	//TODO change this to use update_fbl (or maybe free, and the address of the fbl) and update it with a NULL fbl.
	//write_fbl(&fbl);
	//TODO fix error: typedef not being applied here for some reason
	if (memcmp(get_free_block_list(), &fbl_test_data, sizeof(free_block_list))
			!= 0)
	{
		test_fail("Unit Test Part 2");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 2");
	}

	return EXIT_SUCCESS;
}

int test_update_fbl(void)
{
	/**
	 * Test 1 - test whether we can change the values in the FBL and
	 * compare them to a static test sample
	 */

	const free_block_list fbl_test_data =
	{ .free_blocks =
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 } };

	static free_block_list* fbl = NULL;

	uint32_t test1_used[] = { 2, 4, 6, 7, 8, 9, 14, 15, NULL };
	uint32_t test1_free[] = { 1, 3, 5, 10, 11, 12, 13, 16, 17, 18, NULL };


	free_block_list* test_fbl = update_fbl(test1_used, test1_free);
	if (test_fbl == NULL
			|| memcmp(update_fbl(test1_used, test1_free), &fbl_test_data,
					sizeof(free_block_list)) != 0)
	{
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 1");
	}

	return EXIT_SUCCESS;
}

int test_get_free_block(void)
{
	/**
	 * Test 1 - test whether getting a free block successfully updates the
	 * fbl and gives us a valid address, when the disk has just been initialized
	 */

	//TODO update the contents of this data structure with what's supposed to be in the FBL after initializing the disk
	const free_block_list fbl_test_data_BEFORE =
	{ .free_blocks =
	{ 0 } };

	//TODO update the contents of this dat structure with what's supposed to be in the FBL after getting a single block post-initialization
	const free_block_list fbl_test_data_AFTER =
	{ .free_blocks =
	{ 0 } };

	//TODO reinitialize the file system here

	uint32_t testaddr1 = get_free_block();

	if ((memcmp(get_free_block_list(), &fbl_test_data_AFTER,
			sizeof(free_block_list)) != 0) || testaddr1 == NULL )
	{
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 1");
	}

	/**
	 * Test 2 - test whether getting a free block fails properly if the disk is full
	 */

	//TODO reinitialize the file system here
	//Fill the FBL with full blocks.
	for (int i = 0; i < BLKSIZE; i++)
	{
		update_fbl(i, NULL );
	}

	uint32_t testaddr2 = get_free_block();

	if (testaddr2 != 0)
	{
		test_fail("Unit Test Part 2");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 2");
	}

	return EXIT_SUCCESS;
}
