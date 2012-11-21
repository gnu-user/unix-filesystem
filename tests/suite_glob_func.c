/*
 * suite_glob_func.c
 *
 *  Created on: Nov 20, 2012
 *      Author: ubuntu
 */

#include "suite_glob_func.h"
#include "unit_tests.h"
#include "../src/glob_data.h"
#include <stdlib.h>
#include <string.h>

int test_concat(void)
{

	/* Test 1 -- concat two strings of equal length*/
	char test_destblk1[] = "ABC";
	char test_srcblk1[] = "DEF";
	char result1[] = "ABCDEF";

	char* test1 = concat(&test_destblk1, test_srcblk1, sizeof(char));

	if (strcmp(test1, result1) != 0)
	{
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 1");
	}

	/* Test 2 -- concat two strings, the source is larger than the destination*/
	char test_destblk2[] = "ABC";
	char test_srcblk2[] = "DEFGHI";
	char result2[] = "ABCDEFGHI";

	char* test2 = concat(&test_destblk2, test_srcblk2, sizeof(char));

	if (strcmp(test2, result2) != 0)
	{
		test_fail("Unit Test Part 2");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 2");
	}

	/* Test 3 -- concat two strings, the destination is larger than the source*/
	char test_destblk3[] = "ABCDEF";
	char test_srcblk3[] = "GHI";
	char result3[] = "ABCDEFGHI";

	char* test3 = concat(&test_destblk3, test_srcblk3, sizeof(char));

	if (strcmp(test1, result1) != 0)
	{
		test_fail("Unit Test Part 3");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 3");
	}

	return EXIT_SUCCESS;
}

int test_tokenize_path(void)
{
	/* Test 1 -- tokenize_path using a test path*/
	char ** testtokens = tokenize_path("/test/path");

	if ((testtokens[0] != "test") && (testtokens[1] != "path"))
	{
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	}
	else
	{
		test_pass("Unit Test Part 1");
	}

	/**
	 * Test 2 - tokenize_path using invalid paths
	 * TODO come up with some tests for invalid paths like "/test/crap/path//invalid" or "/./../.../...."
	 * or other paths containing invalid chars like '.' or '\'
	 */
	return EXIT_SUCCESS;
}
