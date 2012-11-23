#include "mount.h"

int validate_super_block(void)
{
	superblock* sb = get_super_block();
	int variant = uuid_variant(sb->uuid);
	if (variant != UUID_VARIANT_DCE) {
		printf("Incorrect UUID Variant; was expecting DCE!\n");
		return -1;
	}
	return 1;
}
