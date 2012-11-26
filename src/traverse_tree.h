
#ifndef TRAVERSE_TREE_H_
#define TRAVERSE_TREE_H_

#include "I_node.h"
#include "error.h"


/**
 * @brief Traverse the file system structure.
 *
 * @details Given the tokens for the path, traverse the file
 * system to either the last token or the second last
 * based on the value in the create flag.
 *
 * @param tokens The pre-parsed pathname tokens.
 *
 * @param create Flags whether to get the parent directory
 * or the child entity if create is true, get the parent. Otherwise,
 * get the child.
 *
 * @return Returns a location on disk. If create is true,
 * the location of the parent is returned and the last token in the
 * tokens array. If create is false, the location of the inode is
 * returned and the second element will be null.
 *
 * @author Daniel Smullen
 *
 * @author Jon Gillett
 *
 * @author Joseph Heron
 *
 * @copyright GNU General Public License V3
 */
extern uint32_t* traverse_file_system(char** tokens, bool create);


#endif /* TRAVERSE_TREE_H_ */
