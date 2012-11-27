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


#include "blockio.h"
#include "close_file.h"


int sfs_close(int fd)
{
	/* Check if a valid file descriptor is given */
	if(fd >= 0 && fd < NUMOFL)
	{

		/* Validate the file descriptor on the System open file table */
		if (validate_fd(fd) < 0)
		{
			print_error(ERROR_UPDATING_SWOFT);
			return 0;
		}

		/* Remove the file descriptor from the System open file table */
		remove_fd(fd);

		/*
		 * 	return value > 0 the file close was a success
		 * 	return value <= 0 the file close was unsuccessful
		 */
		print_error(SUCCESS);
		return 1;
	}
	print_error(UNKNOWN);
	return 0;
}
