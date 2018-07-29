#include <stdlib.h>
#include "tree.h"

/*Private interface fns*/
void    TREE_initNode(tNODE *myNode, tGAME_BOARD board[SIZE][SIZE], int capacity );
tNODE*  TREE_createNode(tGAME_BOARD board[SIZE][SIZE], int capacity);
tNODE*  TREE_addChild(tGAME_BOARD board[SIZE][SIZE], tNODE *parent,int capacity);


int numOfNodes = 0;


void TREE_initNode(tNODE *myNode, tGAME_BOARD board[SIZE][SIZE], int capacity )
{
    myNode->data = 5;
    myNode->board = board;
    myNode->numOfChildren = 0;
    myNode->capacity = capacity;
    myNode->children = (tNODE*)malloc(capacity*sizeof(tNODE));
}


tNODE *TREE_createTree(tGAME_BOARD board[SIZE][SIZE], int capacity)
{
    /*Allocate memory for the root node*/
    tNODE *rtnNode = (tNODE*)malloc(sizeof(tNODE));
    /*Initialize the root and return it*/
    TREE_initNode(rtnNode,board,capacity);
    return rtnNode;
}

tNODE *TREE_createNode(tGAME_BOARD board[SIZE][SIZE], int capacity)
{
    numOfNodes++;
    /*Allocate memory for the root node*/
    tNODE *rtnNode = (tNODE*)malloc(sizeof(tNODE));
    /*Initialize the root and return it*/
    TREE_initNode(rtnNode,board,capacity);
    return rtnNode;
}

tNODE*  TREE_addChild(tGAME_BOARD board[SIZE][SIZE], tNODE *parent,int capacity)
{
    if(parent == NULL ||parent->numOfChildren >= parent->capacity ) return NULL;
    /*Allocate memory & init it*/
    tNODE *child = TREE_createNode(board,capacity);
    /*Branching of each node decreases by 1*/
    child ->capacity = (parent->capacity) -1;
    /*Append the child*/
    parent->children[parent->numOfChildren] = child;
    /*Increase Number of children for future checks*/
    parent->numOfChildren++;
    return child;
}

void TREE_printNumberOfNodes(void)
{
    printf("\nNumber of tree nodes = %d\n",numOfNodes);
}
