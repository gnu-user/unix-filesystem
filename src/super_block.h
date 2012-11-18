/**
 * The structures used for the super_block component of the file system:
 *
 * (Integer) Size of disk (in blocks), which will take up 4 bytes of the block,
 * (Integer) Block size (in bytes), which will take up 4 bytes of the block,
 * A Pointer to the free block linked list, which will take 8 bytes,
 * A Pointer to the Inode table for the root directory, which will take 8 bytes,
 * (Integer) A Device id, which will take up 4 bytes.
*/
#include <stdint.h>
#include "globdata.h"

typedef struct{
	uint32_t size_of_disk;
	uint32_t block_size;
	uint32_t free_block_list;	//Address to the first free block
	uint32_t root_dir;			//Address to the root directory
	uint32_t device_id;
	byte uuid[16];
} superblock;

extern superblock* get_super_block(void);

extern int get_root(void);

extern int get_free_block_index(void);

extern int calc_uuid();

extern int validate_uuid();

/*
 * freeblock
 * add index
 * remove index
 * read index block
 * (static) calculate # of indexes in the current index
 * (static) chain index block (used for linking to next block)
 * (static) iterate thought block (if at the last element in the index block it
 *   should automatically give the first element of the next block
 * (static) return what is at the current location)
 *
 */
