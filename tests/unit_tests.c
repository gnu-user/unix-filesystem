/**
 * The following contains a set of unit tests for testing the project,
 * test cases/unit tests that are organized into test suites are located
 * in source files starting with suite_
 */
#include <stdio.h>
#include "../src/blockio.h"
#include "../src/glob_data.h"

/* Include the test suites */
#include "unit_tests.h"
#include "suite_blockio.h"


/* Displays output stating that it is starting a test suite
 * TODO MAKE A NICE WRAPPER THAT IS MORE HIGH LEVEL, ACTUALLY
 * STARTS A TEST SUITE
 */
start_suite(char* tsuite)
{
	printf(BOLDWHITE "Executing %s Test Suite\n", tsuite);
	puts(BOLDWHITE "========================================\n");
}

//start_test(char* tcase)
start_test(char* name, void* tcase())
{
	printf(BOLDWHITE "Executing %s Test Case\n", name);
	puts(BOLDWHITE "-----------------------------------------\n");

	/* Execute the test case and display the whether the results */

	if (tcase() == EXIT_SUCCESS)
	{
		printf(YELLOW "Test Case %s Passed", name);
	}
	else
	{
		printf(MAGENTA "Test Case %s Failed", name);
	}
}


/*
 * Displays output stating that an individual test has failed
 */
test_fail(char* test)
{
	printf(RED "%s Failed\n", test);
}

/*
 * Displays output stating that an individual test has passed
 */
test_pass(char* test)
{
	printf(GREEN "%s Passed\n", test);
}



/*
 * Execute unit tests if it is defined, otherwise sfs_test.c is main
 */
#ifdef UNIT_TESTING
int main(void)
#else
int unit_test(void)
#endif
{

	/* Start the blockio Test Suite */
	start_suite("blockio");

	/* Execute the get_block test case */
	start_test("get_block", &test_get_block);

	/*
	if (test_get_block() == EXIT_SUCCESS)
	{
		puts(YELLOW "get_block test case Passed");
	}
	else
	{
		puts(MAGENTA "get_block test case Failed");
	}*/

	/* Clear the colours */
	puts(RESET);

	return EXIT_SUCCESS;
}
