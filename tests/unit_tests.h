/*
 * unit_tests.h
 *
 *  Created on: Nov 20, 2012
 *      Author: jon
 */

#ifndef UNIT_TESTS_H_
#define UNIT_TESTS_H_

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


/* Displays output stating that it is starting a test suite
 * TODO MAKE A NICE WRAPPER THAT IS MORE HIGH LEVEL, ACTUALLY
 * STARTS A TEST SUITE
 */
extern start_suite(char * tsuite);

/* Displays output stating that it is starting a test case
 * TODO MAKE A NICE WRAPPER THAT IS MORE HIGH LEVEL, ACTUALLY
 * STARTS A TEST CASE
 */
extern start_test(char * tcase);


#endif /* UNIT_TESTS_H_ */
