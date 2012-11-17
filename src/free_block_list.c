#include "free_block_list.h"

write_fbl(char * buf)
{
	/*
	 1> Read the journal from disk and copy it into a buffer
	 //read_journal();

	 2> Check if the first journal entry contains a LINK_FBL entry:
	 if (journal[0] == NULL) then use the the FBL index from the SB,
	 else use the FBL located at arg1 of the journal_entry at journal[0]

	 //read from the superblock:
	 //read_fbl(0)
	 //location_of_old_fbl = get_free_block_index();

	 //read from the journalled index:
	 //location_of_old_fbl = journal[0].arg1;
	 //read_fbl(location_of_old_fbl);

	 3> Call the update FBL method which updates the FBL entry in memory. It will
	 take the FBL buffer in memory as the first argument, an array of all the
	 indexes to mark as used as the second argument, and an array of all the
	 indexes to mark as unused as the third argument.

	 //next_block = nextAvailableBlock();
	 //sizeOfFBL = ceil(NUMBLOCKS/(BLKSIZE - sizeof(index)));

	 //The indices that need to be marked as freed are the ones we used for the old FBL.
	 // freeBlocks = create a new free_indices: this requires that next_block is called sizeOfFBL times,
	 // and the values returned are added into the free_indices array.

	 //The indices that need to be marked as used are the ones we will be using to store the newly created FBL.
	 //pick sizeOfFBL blocks calc_free_blocks(buf)
	 //update_fbl(buf, freeBlocks, );

	 TODO: replace 2nd and 3rd arguments with actual values, remember the FBL is several blocks so we need to give it
	 or just code it in the .c file DURRR

	 4> Write the FBL to the selected blocks on the hard drive.
	 //loop this statement for all the indices in freeBlocks, using i as an index
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
