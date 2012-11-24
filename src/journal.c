/**
 *
 */

#include "journal.h"

int add_entry(journal_entry* entry) {

	/**
	 * if type = update_fbl, replace entry [0]
	 * Check if this operation exists already (check type, then arg1, then arg2)
	 * 	if so update it
	 * 		replace_entry[i]
	 * 		return err_update(1)
	 * 	if not, add the entry to the journal
	 * 		add_entry[i]
	 * 		return Err_AddJEntry(0)
	 * return Err_InvalidJEntry(-1)
	 */
	return 0;
}

static int sync_journal(void) {
	/**
	 * write the static journal to disk at location JOURNAL (in glob_data.h)
	 *
	 * return err_write_status(n)
	 */
	return 0;
}

int flush_journal(void) {

	/**
	 *	int i = 0;
	 *	while (entry[i] != NULL || i < floor(BLKSIZE/sizeof(entry)))
	 *		execute(entry[i]);
	 *		free(entry[i]);
	 *		i++;
	 *	sync_journal();
	 */
	return 0;
}

int execute (journal_entry entry)
{
	/**
	 * case type:
	 * fbl 0: load SB, change FBL location using arg1, write SB
	 * link 1: load parent's inode (using arg2) using that to load the parent's index, add location (using arg1) to the index , rewrite index
	 * 		read, link, and override the Inode, free the old index blocks
	 * unlink 2: load parent's index (using arg2), find and remove location (using arg1), rewrite index
	 */
	return 0;
}
journal* read_journal(void) {
	return NULL ;
}

static int link_fbl(uint32_t index) {
	return 0;
}

static int link_inode(uint32_t dest_index, uint32_t inode_location) {
	return 0;
}

static int remove_inode(uint32_t dest_index, uint32_t inode_location) {
	return 0;
}

static bool is_journal_full(void) {
	return false;
}
