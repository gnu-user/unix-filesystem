#include "mount.h"

char* INVALID_UUID = "Invalid UUID.\n";

int mount(void)
{
	int status = 0;

	status = validate_super_block();
	if(status == -1)
	{
		printf("Failed to mount disk: superblock uninitialized or corrupted.");
		return -1;
	}

	//journal stuff

	//status = validate_root_dir();

	if(status == -1)
	{
		printf("Failed to mount disk: root directory uninitialized or corrupted.");
		return -1;
	}

	printf("Mount Successful.");

	return 0;
}

int validate_super_block(void)
{
	printf("Validating superblock.");
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
	printf("Validating root directory structure.");
	int variant = uuid_variant(get_uuid(get_root()));
	if (variant != UUID_VARIANT_DCE) {
		printf(INVALID_UUID);
		return -1;
	}
	return 1;
}

