/**
 * @file journal.h
 *
 * The file system journal
 */
#include "glob_data.h"
#include "glob_func.h"

/**
 * Enumeration of the different journal entry types
 * TODO use a byte for entry_type
 *
 * NOTE The -fshort-enums GCC compiler option is used to minimize the
 * size of the enumeration. It will be forced to short type.
 *
 */
typedef enum
{
	LINK_FBL, LINK_BLOCK, UNLINK_BLOCK
} entry_type;

/**
 * The journal_entry data structure is stored in an array (the journal)
 * the first index of the journal array is reserved for the link
 * free_block_list journal entry (if applicable).
 *
 * The remaining entries in the journal are stored as a FIFO queue at indexes
 * greater than 0, as index 0 is reserved for link free_block_list
 *
 */
typedef struct
{
	entry_type type;
	uint32_t arg1;
	uint32_t arg2;
} journal_entry;



/**
 * The Journal contains an array of journal entries, at the moment it is
 * limited to one block (BLKSIZE). The number of entries is limited to the size
 * of one block (BLKSIZE) divided by the size of the journal_entry struct.
 * In a 128 byte block file system, this means there can be 16 entries.
 *
 * TODO malloc floor(BLKSIZE/sizeof(journal_entry) for the journal, since we can't do this dynamically at compile time
 */
typedef struct
{
	journal_entry entry[BLKSIZE];
} journal;

static journal fs_journal;
/**
 * Adds new entries to the journal
 * @param entry The journal_entry to add to the journal
 * @param buf A pointer to the buffer containing the journal to add the entry to
 */
int add_entry(journal_entry* entry);

/**
 * Syncs the journal array in memory with the journal block on disk
 * @param buf A pointer to the buffer containing the journal to be synced
 * @return 0 if successful, EXCEPTION_CODE if an error occurred
 */
static int sync_journal(void);

/**
 * Reads all the entries in the journal, executes, and deletes them
 * @param buf A pointer to the buffer containing the journal to flush
 * @return 0 if successful, EXCEPTION_CODE if an error occurred
 */
extern int flush_journal(void);

/**
 * Reads the journal from disk and copies it into the buffer specified
 *
 * TODO May be able to use an already built-in function to handle this
 */
extern journal* read_journal(void);

/**
 * Links the FBL update in the superblock. The function loads the superblock into
 * memory and edits the FBL location, then rewrites the superblock to the file
 * system
 * @param index The index of the FBL to update in the superblock
 * @return 0 if successful, EXCEPTION CODE if an error occurred
 */
static int link_fbl(uint32_t index);

/**
 * Links an inode into an index block.
 * @param dest_index The index of the inode you wish to link the inode_location inode into
 * @param source_index The location of the inode to be added to the index
 */
static int link_inode(uint32_t dest_index, uint32_t inode_location);

/**
 * Unlinks an inode from an index block.
 * @param dest_index The index of the inode you wish to remove the link the inode_location inode into
 * @param source_index The location of the inode to be remove from the index
 */
static int remove_inode(uint32_t dest_index, uint32_t inode_location);

/**
 * is_journal_full returns a boolean true if the journal is full and false if
 * the journal
 *
 * TODO Should this return a boolean or an 0 if successful, error code if failed?
 * TODO This should be called internally by add_entry
 */
static bool is_journal_full(void);

