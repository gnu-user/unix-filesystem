/**
 * The structures used for the Inode component of the file system:
 *
 * (Char [7]) The file name contains the user name given to the file
 * or directory, it will take up 6 bytes and limited to 6 characters
 * (Boolean) File type identifies whether the index file points to
 * file (0) or a directory (1) which will take up 1 byte.
 * (Boolean) File permissions is whether the file has read, write
 * executable which will take up 4 bytes.
 * (Integer) File created date stores the date the file was created
 * on, and will take up 4 bytes.
 * (Integer) File last accessed date stores the date the file was
 * last accessed on, and will take up 4 bytes.
 * (Integer) File last modified date stores the date the file was
 * last modified on, and will take up 4 bytes.
 * (Integer) File owner stores the user's unique identifier, taking
 * up 4 bytes.
 * (Integer) Last modified stores the unique identifier of the user
 * to last modify the file, and it will take up 4 bytes.
 * (Short Integer) File size stores size of the file, and will take
 * up 2 bytes.
 * (Pointer) Location stores the address of the block on disk, and
 * will take up 4 bytes.
 * (Boolean) The encrypted identifier will identities whether the
 * file is encrypted and will take up 1 byte.
 * (Integer) The check sum of the data (taken before it is
 * encrypted) will take up 4 bytes.
 **/
#include "I_node.h"
#include "block_func.h"

inode get_null_inode()
{
	inode i = {
			.name = "",
			.type = false,
			.read = true,
			.write = true,
			.execute = true,
			.date_of_create = 0,
			.date_last_accessed = 0,
			.date_last_modified = 0,
			.file_owner = 0,
			.last_user_modified = 0,
			.file_size = 0,
			.location = 0,
			.encrypted = false,
			.check_sum = 0
	};
	return i;
}

/**
 * Get the I_node given the block index of the Inode
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return inode pointer of the Inode at the given location.
 * If Inode is null the Inode was not found.
 */
inode* get_inode(int block_num)
{
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return (inode*) buf;
}

/**
 * Get the index block from the Inode given the location of the Inode
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return index integer
 * If index >= 0 then the function was successful,
 * if index < 0 then the function was unsuccessful
 */
uint32_t get_index_block(int block_num)
{
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->location;
}

/**
 * Get the type of the inode, whether it is a directory or a file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return the type of the file
 * If type = 1 then the Inode is for a directory,
 * if type = 0 then the Inode is for a file,
 * otherwise the function has failed.
 */
int get_type(int block_num)
{
	//type
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->type;
}

/**
 * Get size of the file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return the size of the file
 * if the size >= 0 then the function was successful
 * if the size < 0 then the function was unsuccessful
 */
int get_size(int block_num)
{
	/**
	 * Check if the type is a file
	 */
	if (get_type(block_num) != 0)
	{
		return -1;
	}
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->file_size;
}

/**
 * Check if the file is encrypted
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return whether the file is encrypted
 * if encrypt is 0 then the file is not encrypted
 * if encrypt is 1 then the file is encrypted
 * otherwise the function was unsuccessful
 */
int get_encrypted(int block_num)
{
	/**
	 * Check if the type is a file
	 */
	if(get_type(block_num) != 0)
	{
		return 0;
	}

	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return retval;
	}
	return ((inode*) buf)->encrypted;
}

/**
 * Get the name of the file
 *
 * @param block_num integer, the block index of the Inode
 *
 * @return a char pointer to the file's name
 * if the file's name = NULL then the function was unsuccessful
 */
char* get_name(int block_num)
{
	//name[7]
	char* buf = allocate_buf(buf, BLKSIZE);
	int retval = read_block(block_num, buf);

	if(retval != 0)
	{
		return NULL;
	}
	return ((inode*) buf)->name;
}

uint32_t find_inode(locations index_blocks, char* name)
{
	int i = 0;
	while(index_blocks[i] != NULL)
	{
		if(strcmp(get_name(index_blocks[i]),name)==0)
		{
			return index_blocks[i];
		}
		i++;
	}
	return 0;
}
