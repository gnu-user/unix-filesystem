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

	//This will act as our static FBL in memory. We will also use this
	//value as our test string.
	const free_block_list* fblTestData = {1,0,1,1,0,1,1,1,1,0,1,1,0,1,0,0};
	static free_block_list* fbl;
	memcpy(fbl, fblTestData, sizeof(free_block_list));

	/**
	 * Test 1 - test whether we can retrieve the fbl from our local static instance
	 */

	static free_block_list* test_fbl1;
	test_fbl1 = get_free_block_list(fbl);

	/**
	 * TODO verify that free_block_list is the size we want, not sizeof(bool)
	 */
	if (!memcmp(fbl, test_fbl1,sizeof(free_block_list)))
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

	free(fbl);
	static free_block_list* test_fbl2;

	test_fbl2 = get_free_block_list(fbl);

	/**
	 * TODO verify that free_block_list is the size we want, not sizeof(bool)
	 */
	if (!test_fbl2 || !fbl || memcmp(fbl,fblTestData,sizeof(free_block_list)))
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
	 * Test 1 - test
	 */

	if (0)
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
	 * Test 1 - test
	 */

	if (0)
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
