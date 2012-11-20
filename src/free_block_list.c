#include "free_block_list.h"
#include <stdbool.h>


free_block_list* get_free_block_list(void)
{
	return NULL;
}


free_locations calc_total_free_blocks(void)
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


free_locations calc_num_free_blocks(uint32_t num_blocks)
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
}


free_location get_free_block(void)
{
/*
	free_block = calc_free_blocks(fbl, 1);

	update_fbl(fbl, free_block);

	return free_block;
*/
}


/**
 * TODO Make the return type for this int and other functions returning int into the ERROR_CODES enumeration.
 */
int write_fbl(void)
{
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

static free_block_list* iterate_fbl(uint32_t index)
{

	return NULL;
}


free_block_list* update_fbl(used_locations used,
							free_locations free)
{
 	/* Iterate through each item in the used and free locations array,
 	 * for each item in the array update the free block list
	 */
	if (used != NULL)
	{
		uint32_t i = 0;

		/*while (used[i] != NULL)
		{
			// Mark each of the fbl locations specifed as used
			fbl[used[i]] = true;
			++i;
		}*/

	}
	if (free != NULL)
	{
		uint32_t i = 0;

		/*while (free[i] != NULL)
		{
			// Mark each of the fbl locations specifed as free
			fbl[free[i]] = false;
			++i;
		}*/

	}

	return fbl;
}
