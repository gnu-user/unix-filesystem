TESTS
=====

rebuild_index test
------------------

* The following is added to initialize after free_block_init()

/* TEST -- GENERATE INDEX FOR 1 BLOCK */
/* Test locations */
uint32_t test_locations[] = {36, 37, 38, 67, 69, 70, 100, NULL };
uint32_t test_locations2[] = { NULL };

/* TEST FOR rebuild_index, it should return the location of the first index */
uint32_t index_location1 = rebuild_index(test_locations);
uint32_t index_location2 = rebuild_index(test_locations2);

/* Verify the data location results */
locations data_locations = iterate_index(index_location1, NULL);
locations data_locations2 = iterate_index(index_location2, NULL);

/* Verify the index location results */
locations index_block_locations = index_block_locations(index_location1, NULL);
locations index_block_locations2 = index_block_locations(index_location2, NULL);


rebuild_index test 2
--------------------

/* TEST -- GENERATE INDEX FOR 1 BLOCK */
/* Test locations */
uint32_t test_locations[66] = { NULL };
uint32_t test_locations2[12] = { NULL };

for (uint32_t i = 0; i < 65; ++i)
{
	test_locations[i] = 100 + i;
}

for (uint32_t i = 0; i < 11; ++i)
{
	test_locations2[i] = 200 + i;
}

/* TEST FOR rebuild_index, it should return the location of the first index */
uint32_t index_location1 = rebuild_index(test_locations);
uint32_t index_location2 = rebuild_index(test_locations2);

/* Verify the data location results */
locations data_locations1 = iterate_index(index_location1, NULL);
locations data_locations2 = iterate_index(index_location2, NULL);

/* Verify the index location results */
locations first_index_location1 = index_block_locations(index_location1, NULL);
locations first_index_location2 = index_block_locations(index_location2, NULL);