/*
 * SneakyFS - A Secure UNIX File System
 *
 * Copyright (C) 2012, Jonathan Gillett, Joseph Heron, and Daniel Smullen
 * All rights reserved.
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "system_open_file_table.h"

swoft system_open_tb = {0};

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
	system_open_tb.fd[index] = block_num;
	system_open_tb.taken[index] = true;

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
		if(system_open_tb.taken[i] == false)
		{
			return i;
		}
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

inode get_swoft_inode(int fd)
{
	return (inode) *get_inode(system_open_tb.fd[fd]);
}

uint32_t get_inode_loc(int fd)
{
	return system_open_tb.fd[fd];
}

void remove_fd(int fd)
{
	system_open_tb.taken[fd] = false;
}

uint32_t find_and_remove(uint32_t inode_location)
{
	uint32_t count = 0;

	for(int i = 0; i < NUMOFL; i++)
	{
		if(system_open_tb.taken[i] == true)
		{
			if(system_open_tb.fd[i] == inode_location)
			{
				system_open_tb.taken[i] = false;
				system_open_tb.fd[i] = 0;
				count++;
			}
		}
	}
	return count;
}
