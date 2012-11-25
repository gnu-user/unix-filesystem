
#ifndef TRAVERSE_TREE_H_
#define TRAVERSE_TREE_H_

#include "I_node.h"
#include "error.h"

/**
 * Given the tokens for the path traverse the file system to either the last
 * token or the second last base on the create flag
 *
 * @param tokens the parsed pathname
 * @param whether to get the parent directory or the child
 * if create == true get the parent
 * otherwise get the child
 *
 * @return
 * if create == true, the location of the parent and the last token in the
 * tokens array
 * if create == false, the location of the inode and the second element will be
 * null
 */
extern uint32_t* traverse_file_system(char** tokens, bool create);

#endif /* TRAVERSE_TREE_H_ */
