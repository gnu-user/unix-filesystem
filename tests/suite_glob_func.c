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

int test_concat(void) {
	/* Test 1 -- concat  */
	//TODO perform an actual test here and check the output
	if (0) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	return EXIT_SUCCESS;
}

int test_tokenize_path(void) {
	/* Test 1 -- tokenize_path using a test path*/
	char ** testtokens = tokenize_path("/test/path");

	if ((testtokens[0] != "test") && (testtokens[1] != "path")) {
		test_fail("Unit Test Part 1");
		return EXIT_FAILURE;
	} else {
		test_pass("Unit Test Part 1");
	}

	/**
	 * Test 2 - tokenize_path using invalid paths
	 * TODO come up with some tests for invalid paths like "/test/crap/path//invalid" or "/./../.../...."
	 * or other paths containing invalid chars like '.' or '\'
	 */
	return EXIT_SUCCESS;
}
