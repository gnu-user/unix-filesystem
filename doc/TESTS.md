TESTS
=====

index_block_locations test
--------------------------

/* TEST FOR index_block_locations, call index_block_locations given the
 * first index location, it should return a NULL terminated locations array
 * with the index location
 */
locations test_idx_locations = NULL;

test_idx_locations = index_block_locations(idx.index_location, NULL);

if (test_idx_locations == NULL)
{
	return NULL;
}
	

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


get_free_block_list / reset_fbl
--------------------------------

* Mark specific points in the FBL on disk as true, execute
  get_free_block_list and verify that the fbl in memory has been
  updated

0 - 5 = true
120 = true
154 = true
255 = true
390 = true
499 = true
511 = true


/* TEST -- get_free_block_list */
free_block_list* test_fbl = NULL;
test_fbl = get_free_block_list();


sync_fbl
---------

* Similarly to get_free_block_list, mark specific locations in the disk as
  used and then read them into memory, then alter the FBL in memory
  significantly and execute sync_fbl, then call reset_fbl, the contents of
  memory should be the same as what was just sync'd to disk

0 - 9 = true
120 - 129 = true
255 - 264 = true
500 - 511 = true

/* TEST -- get_free_block_list */
free_block_list* test_fbl = NULL;
free_block_list* test_fbl2 = NULL;
free_block_list* test_sync_fbl = NULL;
test_fbl = get_free_block_list();

/* Update the fbl in memory */
uint32_t free[35] = { 1, 2, 3, 4, 5, 6, 7 , 8, 9, 10,
					120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
					500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, NULL };

uint32_t used[11] = {401, 402, 403, 404, 405, 406, 407, 408, 409, 410, NULL };

test_fbl2 = update_fbl(used, free);

/* Now sync the new FBL in memory to disk */
test_sync_fbl = sync_fbl();





