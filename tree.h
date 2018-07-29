#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "type.h"
#include "conf.h"


tNODE *TREE_createTree(tGAME_BOARD board[SIZE][SIZE], int capacity);
void  TREE_printNumberOfNodes(void);


#endif // TREE_H_INCLUDED
