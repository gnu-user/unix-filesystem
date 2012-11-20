#include "unit_tests.h"
#include "../src/glob_data.h"
#include <stdlib.h>

/*
 * get_block test case
 */
int test_get_block(void)
{
	byte temp[128] = {0};
	int blknum = 1000;

	/* Start the get_block test case */
	//start_test("get_block");

	/* Test 1 -- get_block with a block that exists */
	if (get_block(blknum, temp) != 0)
	{
		test_fail("Unit Test 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test 2");
	}

	return EXIT_SUCCESS;
}
