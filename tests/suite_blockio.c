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

	/* Test 1 -- get_block with a block that exists */
	if (get_block(blknum, temp) != 0)
	{
		puts(RED "[get_block][Unit Test 1] Failed");
		return EXIT_FAILURE;
	}
	else
	{
		puts(GREEN "[get_block][Unit Test 1] Passed");
	}

	return EXIT_SUCCESS;
}
