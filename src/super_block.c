//(Integer) Size of disk (in blocks), which will take up 4 bytes of the block,
//(Integer) Block size (in bytes), which will take up 4 bytes of the block,
//A Pointer to the free block linked list, which will take 8 bytes,
//A Pointer to the Inode table for the root directory, which will take 8 bytes,
//(Integer) A Device id, which will take up 4 bytes.

struct super_block
{
	int size_of_disk;
	int block_size;
	int free_block_list;	//Address to the first free block
	int root_dir;			//Address to the root directory
	int device_id;
};