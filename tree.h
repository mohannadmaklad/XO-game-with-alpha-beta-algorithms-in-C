#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "type.h"
#include "conf.h"

extern int count;
extern int numOfNodes;

tNODE   *TREE_createTree(tGAME_BOARD board[SIZE][SIZE], int capacity);
void    TREE_printNumberOfNodes(void);
void    TREE_destroyTree(tNODE *root);

#endif // TREE_H_INCLUDED
