#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "type.h"
#include "conf.h"

extern int count;
extern int numOfNodes;

tNODE*  TREE_createNode(tGAME_BOARD board[SIZE][SIZE], int capacity);
tNODE*  TREE_addChild(tGAME_BOARD board[SIZE][SIZE], tNODE *parent,int capacity);
void    TREE_printNumberOfNodes(void);
void    TREE_destroyTree(tNODE *root);
void    TREE_initNode(tNODE *myNode, tGAME_BOARD board[SIZE][SIZE], int capacity );
void    Tree_countTree(tNODE *root);

#endif // TREE_H_INCLUDED
