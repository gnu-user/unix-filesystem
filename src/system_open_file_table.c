/**
 * System wide open file table
 * Needs to have at least 5 instances (to have 5 files open at once)
 **/
#include "system_open_file_table.h"

swoft system_open_tb = {0};

/**
 * Add the inode to the swoft
 *
 * @param block_num location, the Inode's location on disk
 *
 * @param an integer value,
 * if the value >= 0 then the inode was found and added to the swoft
 * if the value == -1 then the swoft was full
 * if the value == -2 then the inode was not found
 * otherwise the function was unsuccessful
 */
int add_to_swoft(uint32_t block_num)
{
	inode* test = NULL;
	int index = -1;

	index = find_opening();


	/**
	 * The swoft is full
	 */
	if(index < 0)
	{
		return -1;
	}

	/**
	 * Retrieve the Inode
	 */
	test = get_inode(block_num);

	/**
	 * Check if the Inode was found
	 */
	if(test == NULL)
	{
		return -2;
	}

	/**
	 * Store the Inode in the swoft
	 */
	//TODO de-reference...
	system_open_tb.fd[index] = *test;

	/**
	 * return the file descriptor (index)
	 */
	return index;
}

/**
 * Find an open location in the swoft
 *
 * @return an integer value,
 * if value >= 0 then it is the first location in the swoft that is available
 * if value < 0 then the swoft is full
 */
int find_opening(void)
{
	for(int i = 0; i < NUMOFL; i++)
	{
		//TODO fix comparison
		if(system_open_tb.taken[i] == false)
		{
			return i;
		}

		//Temp
		return 0;
	}

	return -1;
}

int validate_fd(int fd)
{
	if(system_open_tb.taken[fd] == true)
	{
		return 0;
	}
	return -1;
}

inode get_swoft_inode(fd)
{
	return system_open_tb.fd[fd];
}
