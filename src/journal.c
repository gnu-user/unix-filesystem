/**
 *
 */

#include "journal.h"

journal* add_entry(journal_entry* entry, journal* buf) {

	return NULL ;
}

static int sync_journal(journal *buf) {
	return 0;
}

int flush_journal(journal *buf) {
	return 0;
}

journal* read_journal(journal *buf) {
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

static bool is_journal_full(void)
{
	return false;
}
