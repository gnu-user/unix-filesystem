#include "mount.h"

char* INVALID_UUID = "Invalid UUID.\n";

int mount(void)
{
	int status = 0;

	printf("Validating superblock.\n");
	status = validate_super_block();
	if(status == -1)
	{
		// TODO add error code and message
		printf("Failed to mount disk: superblock uninitialized or corrupted.\n");
		return -1;
	}

	printf("Validating root directory structure.\n");
	status = validate_root_dir();

	if(status == -1)
	{
		// TODO add error code and message
		printf("Failed to mount disk: root directory uninitialized or corrupted.\n");
		return -1;
	}

	/* Initialize the free block list in memory with the fbl from disk */
	if (get_free_block_list() == NULL)
	{
		// TODO add error code and message
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
		// TODO add error code and message
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
		// TODO add error code and message
		printf(INVALID_UUID);
		return -1;
	}
	return 1;
}

