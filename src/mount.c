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


#include "mount.h"

char* INVALID_UUID = "Invalid UUID.\n";


int mount(void)
{
	int status = 0;

	printf("Validating superblock.\n");
	status = validate_super_block();
	if(status == -1)
	{
		printf("Failed to mount disk: superblock uninitialized or corrupted.\n");
		return -1;
	}

	printf("Validating root directory structure.\n");
	status = validate_root_dir();

	if(status == -1)
	{
		printf("Failed to mount disk: root directory uninitialized or corrupted.\n");
		return -1;
	}

	/* Initialize the free block list in memory with the fbl from disk */
	if (get_free_block_list() == NULL)
	{
		printf("Failed to read and/or update the free block list.\n");
		return -1;
	}

	printf("Mount Successful.");

	return 0;
}


int validate_super_block(void)
{
	superblock* sb = get_super_block();
	int variant = uuid_variant(sb->uuid);
	if (variant != UUID_VARIANT_DCE) {
		printf(INVALID_UUID);
		return -1;
	}
	return 1;
}


int validate_root_dir(void)
{
	uuid_t* uuid_root = get_uuid(get_root());

	int variant = uuid_variant(uuid_root);
	if (variant != UUID_VARIANT_DCE) {
		printf(INVALID_UUID);
		return -1;
	}
	return 1;
}

