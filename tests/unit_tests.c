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
#include "suite_glob_func.h"
#include "suite_free_block_list.h"

/* Displays output stating that it is starting a test suite
 */
start_suite(char* tsuite) {
	printf(BOLDWHITE "\nExecuting %s Test Suite\n" RESET, tsuite);
	puts(BOLDWHITE "========================================" RESET);
}

//start_test(char* tcase)
start_test(char* name, void* tcase()) {
	printf(BOLDWHITE "\nExecuting %s Test Case\n" RESET, name);
	puts(BOLDWHITE "-----------------------------------------\n" RESET);

	/* Execute the test case and display the whether the results */

	if (tcase() == EXIT_SUCCESS) {
		printf(BOLDGREEN "\nTest Case %s Passed\n" RESET, name);
	} else {
		printf(BOLDRED "\nTest Case %s Failed\n" RESET, name);
	}
}

/*
 * Displays output stating that an individual test has failed
 */
test_fail(char* test) {
	printf(BOLDMAGENTA "%s Failed\n" RESET, test);
}

/*
 * Displays output stating that an individual test has passed
 */
test_pass(char* test) {
	printf(BOLDBLUE "%s Passed\n" RESET, test);
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
	/***************************************************************/

	/* Start the blockio Test Suite */
	start_suite("blockio");
	/* Execute the get_block test case */
	start_test("get_block", &test_get_block);
	/* Execute the put_block test case */
	start_test("put_block", &test_put_block);

	/***************************************************************/

	/* Start the global functions test suite */
	start_suite("glob_func");
	/* Execute the concat test case */
	start_test("concat", &test_concat);
	/* Execute the tokenize_path test case */
	start_test("tokenize_path", &test_tokenize_path);

	/***************************************************************/

	/* Start the free_block_list test suite */
	start_suite("free_block_list");
	/* Execute the get_free_block_list test case */
	start_test("get_free_block_list", &test_get_free_block_list);
	/* Execute the update_fbl test case */
	start_test("update_fbl", &test_update_fbl);
	/* Execute the get_free_block test case */
	start_test("get_free_block", &test_get_free_block);

	/***************************************************************/

	/* Start the index_block test suite */
	start_suite("index_block");
	/* Execute the generate_index test case */
	start_test("generate_index", &test_generate_index);
	/* Execute the iterate_index test case */
	start_test("iterate_index", &test_iterate_index);
	/* Execute the get_free_block_list test case */
	start_test("calc_index_blocks", &test_calc_index_blocks);

	/***************************************************************/

	/* Clear the colours */
	puts(RESET);

	return EXIT_SUCCESS;
}
