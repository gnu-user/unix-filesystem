/**
 * The following contains a set of unit tests for testing the project,
 * test cases/unit tests that are organized into test suites are located
 * in source files starting with suite_
 */
#include <stdio.h>
#include "../src/blockio.h"
#include "../src/glob_data.h"

/* Define colours for colored output of unit test results */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


/*
 * blockio get_block test case
 */
int test_get_block(void)
{
	byte temp[128] = {0};
	int blknum = 0;

	/* Test 1 -- get_block with a block that exists*/
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

/*
 * Execute unit tests if it is defined, otherwise sfs_test.c is main
 */
#ifdef UNIT_TESTING
int main(void)
#else
int unit_test(void)
#endif
{
	puts(BOLDWHITE "Executing Blockio Test Suite");
	puts(BOLDWHITE "============================");
	puts(BOLDWHITE "Executing get_block test case:");
	if (test_get_block() == EXIT_SUCCESS)
	{
		puts(YELLOW "get_block test case Passed");
	}
	else
	{
		puts(MAGENTA "get_block test case Failed");
	}

	/* Clear the colours */
	puts(RESET);

	return EXIT_SUCCESS;
}
