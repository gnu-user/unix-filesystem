File System Test Cases
=======================

Overview
--------

A test case is usually a single step, or occasionally a sequence of steps, to test
the correct behaviour/functionalities, features of an application. An expected result
or expected outcome is usually given.

Additional information that may be included:
* test case ID
* test case description
* test step or order of execution number
* related requirement(s)
* depth
* test category
* author
* check boxes for whether the test is automatable and has been automated.
* Expected Result and Actual Result.
* Additional fields that may be included and completed when the tests are executed:
* pass/fail
* remarks

Larger test cases may also contain prerequisite states or steps, and descriptions.
A written test case should also contain a place for the actual result.

These steps can be stored in a word processor document, spreadsheet, database or 
other common repository.

Test suites often also contain:
* Test summary
* Configuration


Suggestions
-----------

We have very primitive low-level test-cases that are executed *first*, these are just per
function calls, these per-function calls are grouped into test suites by file/relationship.

After we have the primitive test cases done for each function we feel necessary to write a
test case for we could have a few test suites for different operations such as journaling,
tree traversal, etc. In these test suites we might have several already defined test cases
executed.


Example
-------

The following is an example for index block test suite

Index Block
------------

### generate_index : One block // Test case ID, could be test case function name so it's easy to figure out what its for

Test Case Description: Tests the generate_index block for one block of data

Test Execution:
* Initialize a blank disk: initialize_disk(true)
* Generate index for 1 data block: (generate_index(1)
* Verify that the location of the index block
* Verify the contents of the index block (get_block(...)) 

Test Input:
* initialize_disk(true)
* generate_index(1)

Expected Result:
* location of the index block == 5
* contents of the index block  [6, 0]


References
----------

See the following links, try googling around for a few examples, although there are 
some sites with REALLY bad examples.

* [Test Cases](http://en.wikipedia.org/wiki/Test_case)
* [Unit Testing](http://en.wikipedia.org/wiki/Unit_testing)
* [Test Driven Development](http://en.wikipedia.org/wiki/Test-driven_development)
* [How to write test cases](http://templateforfree.com/how-to-write-test-cases/)
* [Software Testing](http://en.wikipedia.org/wiki/Software_testing)