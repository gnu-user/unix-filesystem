Test Cases
==========

free_block_list Test Suite
--------------------------

### get_free_block_list Test Case

* Initialize the free_block_list fbl array with some of the first blocks marked as
used and verify that the results of get_free_block_list matches the fbl in memory

### update_fbl Test Case

* Execute the test with a pre-defined used and free locations arrays and verify that the results from update_fbl match the expected values in fbl

### get_free_block Test Case

* Execute the test with pre-defined fbl and verify that it actually returns the right location for the next free block available and that the fbl in memory is correctly updated by get_free_block

* If the get_free_block_list test case passes then you can use it to return the fbl currently set in memory to compare against the expected fbl if the get_free_block function works


index_block Test Suite
--------------------------

### generate_index Test Case

* This test case has a dependency, it relies on the write_block, read_block, and 
intialize test cases working, as you need to initialize the disk and write each index, and read the indexes from disk to make sure they are correct

* This test is executed using a pre-defined number of blocks to write and a pre-defined result for the index read into memory

1. Initilize the file system
2. generate index for the pre-defined num_blocks
3. read_block the index
4. verify that the contents in the index read from disk match the expected index contents

### iterate_index Test Case

* This test case has a **dependency** on the generate_index test case

* This test case has a dependency, it relies on the generate_index, write_block, 
read_block, and intialize test cases working, as you need to initialize the disk and write each index, and read the indexes from disk to make sure they are correct

* This test is executed using a pre-defined number of blocks to write and a pre-defined result for the index read into memory and predefined locations that should
be returned (you can re-use a lot of code from generate_index test case)

1. Initilize the file system
2. generate index for the pre-defined num_blocks
3. iterate index using the first index location returned in the data_index structure return by generate index step
4. verify that the locations returned by iterate index match the expected locations

### count_locations Test Case

* This test is basically identical to iterate_index test case, count_locations  
is a WRAPPER  for iterate_index, except that it just returns the count of locations

* Execute this test with a pre-defined expected count for the data locations

### index_block_locations Test Case

* This test is similar to iterate_index test case, index_block_locations just returns the locations of index blocks

* This test is executed using a pre-defined number of blocks to write and a pre-defined result for the index read into memory and predefined locations that should
be returned (you can re-use a lot of code from iterate_index test case)


traverse_tree Test Suite
------------------------

These test cases are important as we must be able to actually traverse the file system.

### traverse_file_system Test Case

This function has a test dependency and requires all of the following test cases to pass:

* tokenize_path
* get_root
* get_index_block
* iterate_index
* find_inode
* get_index_block

The test case should have the following conditions

* Have a set of pre-defined paths (valid, invalid, etc.), execute tokenize_path 
which should pass the test cases for paths
* Execute traverse_file_system with the path tokens returned from tokenize_path
* Execute traverse_file_system with a condition create = true, and create = false
* Verify the results match the pre-defined expected results