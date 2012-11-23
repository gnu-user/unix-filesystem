#include "free_block_list.h"
#include <stdbool.h>

static free_block_list fbl =
{
	.free_blocks = { false }
};


free_block_list* get_free_block_list(void)
{
	uint32_t fbl_location = 0;
	free_block_list* tmp_fbl = NULL;

	/* If the current free block list in memory has not been set (the
	 * superblock at index 0 is marked as 0) read the FBL from disk
	 */
	if (fbl.free_blocks[0] == false)
	{
		/* Read the FBL from disk and update the instance in memory */
		fbl_location = get_free_block_index();
		tmp_fbl = read_fbl(fbl_location);

		if (tmp_fbl != NULL)
		{
			/* Overwrite the current fbl with the fbl from disk */
			memcpy(&fbl, tmp_fbl, sizeof(free_block_list));

			/* Free the temp fbl buffer */
			free(tmp_fbl);
		}
		else
		{
			return NULL;
		}
	}

	return &fbl;
}


locations calc_total_free_blocks(void)
{
	//1. Get the free block list.
	//2. Traverse it and add any blocks marked as empty to an array of type free_indices.
	//3. Return the array.

/*
	locations_buf = calloc(NUMBLKS, sizeof(free_location))
	count = 0

	for (i = 0, i < NUMBLKS, i++)
	{
		if (! fbl[i])
		{
			locations_buf[count] = i
			count++
		}
	}

	return locations_buf

 */

}


locations calc_num_free_blocks(uint32_t num_blocks)
{
	//1. Get the free block list.
	//2. Traverse it and add num_blocks specified marked as empty to an array of type free_indices.
	//3. Return the array.

	/*
	    // num_blocks + 1 items in order to null terminate
		locations_buf = calloc(num_blocks +1, sizeof(free_location))
		count = 0

		for (i = 0, i < NUMBLKS, i++)
		{
			// If found the num_blocks specified break
			if (count == num_blocks)
			{
				break;
			}
			if (! fbl[i])
			{
				locations_buf[count] = i
				count++
			}
		}

		return locations_buf

	 */
	return 9;
}


uint32_t get_free_block(void)
{
	/* Get the location of the next available free block */
	locations free_block = calc_num_free_blocks(1);
	uint32_t free_block_loc = 0;

	/* If the free_block is NULL there are no more free blocks available */
	if (free_block == NULL)
	{
		return 0;
	}

	/* Mark the free_block location as used in the free block list and return the location */
	if (update_fbl(free_block, NULL ) != NULL)
	{
		/* Copy the single free block location and free the dynamic memory */
		free_block_loc = free_block[0];
		free(free_block);

		return free_block_loc;
	}

	/* Otherwise, an error occurred updating the free block list */
	return 0;
}


/**
 * TODO Make the return type for this int and other functions returning int into the ERROR_CODES enumeration.
 */
bool write_fbl(free_block_list* current_fbl)
{
	//TODO USE THE POINTER TO current_fbl FOR WHAT TO WRITE TO DISK!
	/*
	 //Check if the first journal entry contains a LINK_FBL entry:
	 if (journal[0] == NULL)
	 {
	 //then use the the FBL index from the SB,
	 //read from the superblock:extern used_indices*
	 location_of_fbl = get_free_block_index();
	 }

	 else{
	 //else use the FBL located at arg1 of the journal_entry at journal[0]
	 //read from the journalled index:
	 location_of_fbl = journal[0].arg1;
	 }

	 //update the current free block list by marking the existing FBL's blocks as unused.
	 update_fbl(buf, index_fbl_blocks(location_of_fbl), calc_free_blocks(fbl, ));



	 3> Call the update FBL method which updates the FBL entry in memory. It will
	 take the FBL buffer in memory as the first argument, an array of all the
	 locations to mark as used as the second argument, and an array of all the
	 locations to mark as unused as the third argument.



	 //The indices that need to be marked as freed are the ones we used for the old FBL.
	 // freeBlocks = create a new free_indices: this requires that next_block is called sizeOfFBL times,
	 // and the values returned are added into the free_indices array.

	 //The indices that need to be marked as used are the ones we will be using to store the newly created FBL.
	 //pick sizeOfFBL blocks calc_free_blocks(buf)
	 //update_fbl(buf, freeBlocks, );

	 TODO: replace 2nd and 3rd arguments with actual values, remember the FBL is several blocks so we need to give it
	 or just code it in the .c file DURRR

	 4> Write the FBL to the selected blocks on the hard drive.
	 //loop this statement for all the locations in freeBlocks, using i as a location
	 //{
	 //    put_block(freeBlocks[i], );
	 //}

	 5> Journal the linking of the newly created FBL within the superblock.

	 //add the journal entry:
	 //add_entry_journal();

	 //sync the journal:
	 //sync_journal();

	 //journal the linkage to the SB:
	 //link_fbl();

	 */
}


static free_block_list* read_fbl(uint32_t location)
{
	/*
	 --> Calls the iterate_fbl which iterates through the nodes in the
	 free_block_list linked list
	 */
	return NULL;
}


/*
 * TODO REMOVE THIS, IT IS ONLY IN THE NON-INDEXED VERSIONS OF FBLS, WE NOW CALL GENERATE
 * INDEX TO CREATE INDICES FOR A NEW INSTANCE OF AN FBL ON THE DISK

static used_locations index_fbl_blocks(uint32_t index)
{

}
*/

static free_block_list* iterate_fbl(uint32_t location)
{

	return NULL;
}


free_block_list* update_fbl(locations used,
							locations free)
{
 	/* Iterate through each item in the used and free locations array,
 	 * for each item in the array update the free block list
	 */

	// TODO need to handle properly setting the first fbl index as used by the superblock
	fbl.free_blocks[0] = true;

	uint32_t i = 0;

	if (used != NULL)
	{
		while (used[i] != NULL)
		{
			/* Mark each of the fbl locations specifed as used */
			fbl.free_blocks[used[i]] = true;
			++i;
		}
	}
	if (free != NULL)
	{
		i = 0;

		while (free[i] != NULL)
		{
			/* Mark each of the fbl locations specifed as free */
			fbl.free_blocks[free[i]] = false;
			++i;
		}
	}

	return &fbl;
}
