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

/* TEST -- REBUILD INDEX */
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


segment_data test 1
-------------------

/* TEST -- Modify data */
/* Test locations */
byte test_buf[514] = { NULL };

for (uint32_t i = 0; i < 513; ++i)
{
	test_buf[i] = (byte)'A';
}

/* Array of data blocks */
block* data_blocks = NULL;

data_blocks = segment_data(test_buf);


segment_data
-------------

/* TEST -- Modify data */
/* Test locations */
byte test_buf[65] = { NULL };

for (uint32_t i = 0; i < 64; ++i)
{
	test_buf[i] = (byte)'A';
}

/* Array of data blocks */
block* data_blocks = NULL;

data_blocks = segment_data(test_buf);





modify_data Test 1
------------------

/* TEST -- Modify data */
/* Test locations */
byte test_buf[314] = { NULL };
byte input_buf[44] = { NULL };

for (uint32_t i = 0; i < 313; ++i)
{
	test_buf[i] = (byte)'A';
}

for (uint32_t i = 0; i < 43; ++i)
{
	input_buf[i] = (byte)'B';
}

/* Offset and length for modify data */
uint32_t start = 200;
uint32_t length = 43;

/* Array of data blocks */
block* data_blocks = NULL;


modify_data Test 2 -- Append data
---------------------------------

* Append half a block worth of data

/* TEST -- Modify data */
/* Test locations */
byte test_buf[355] = { NULL };
byte input_buf[65] = { NULL };

for (uint32_t i = 0; i < 354; ++i)
{
	test_buf[i] = (byte)'A';
}

for (uint32_t i = 0; i < 64; ++i)
{
	input_buf[i] = (byte)'B';
}

/* Offset and length for modify data */
int32_t start = -1;
uint32_t length = 64;

/* Array of data blocks */
block* data_blocks = NULL;

/* Modify the test buffer with the input buf */
data_blocks = modify_data(start, length, test_buf, input_buf);


modify_data Test 2 -- Append multiple blocks of data
----------------------------------------------------

* Append multiple blocks worth of data

byte test_buf[355] = { NULL };
byte input_buf[355] = { NULL };







