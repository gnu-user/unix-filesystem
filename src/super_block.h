/**
 * The structures used for the superblock component of the file system
 */

/**
 * (Integer) Size of disk (in blocks), which will take up 4 bytes of the block,
 * (Integer) Block size (in bytes), which will take up 4 bytes of the block,
 * A Pointer to the free block linked list, which will take 8 bytes,
 * A Pointer to the Inode table for the root directory, which will take 8 bytes,
 * (Integer) A Device id, which will take up 4 bytes.
*/
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	uint32_t size_of_disk;
	uint32_t block_size;
	uint32_t free_block_list;	//Address to the first free block
	uint32_t root_dir;			//Address to the root directory
	uint32_t device_id;
} superblock;

/*typedef struct{
	bool blocks[];
} freeblock;
*/
//extern bool blocks[];
