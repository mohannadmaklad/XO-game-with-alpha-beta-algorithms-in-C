#include "game.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//#define prune  //works well
/*Private interfaces*/
int     GAME_heur(tGAME_BOARD board[SIZE][SIZE]);
int     GAME_isTerminal(tGAME_BOARD board[][SIZE]);
int     GAME_AlphaBeta(tNODE *n, int alpha, int beta,int maximizing);
void    GAME_generateChildren(tNODE *n,tGAME_BOARD board[SIZE][SIZE], char player);
tNODE*  GAME_getMinHeur(tNODE *parent);
void    GAME_constructTree(void);
tNODE*  GAME_findChild(tNODE *parent,tNODE *possibleChild);


 tGAME_BOARD buffer[SIZE][SIZE];
 tGAME_BOARD initialBoard[SIZE][SIZE];

tPLAYER currentPlayer = COMPUTER;
tNODE *currentRoot;
tNODE *currentNode, *tmpNode;


void GAME_init(void)
{
    int i,j;
    for( i=0; i<SIZE;i++)
    {
        for( j=0; j<SIZE;j++)
        {
            initialBoard[i][j]= ' ';
        }
    }
#ifdef debug
    //initialBoard[0][0] = 'o';
    //initialBoard[0][1] = 'o';
    //initialBoard[0][2] = 'o';
    //initialBoard[1][0] = 'o';
    //initialBoard[1][1] = 'x';
    //initialBoard[2][0] = 'x';
    //initialBoard[2][2] = 'x';
#endif
    currentNode = TREE_createTree(initialBoard,(SIZE*SIZE));
    currentRoot = currentNode;
    //if successfully allocated, construct the tree
    if(currentNode)
    {
        printf("\nConstructing the tree..\n");
        GAME_AlphaBeta(currentNode,-1000,1000,!currentPlayer);
        printf("\nDone :)\n");
    }
}

tGAME_BOARD** GAME_getBoard()
{
    return currentNode -> board;
}

tGAME_BOARD** GAME_getABuffer()
{
    return buffer;
}


void GAME_getBestMove(void)
{
    currentNode = GAME_getMinHeur(currentNode);
}

int GAME_isGameOver(void)
{
    return GAME_isTerminal(currentNode->board);
}

void GAME_switchTurns(void)
{
    currentPlayer = !currentPlayer;
}

void GAME_declareWinner(void)
{
    if(GAME_heur(GAME_getBoard()) == 1) printf("human wins");
    else if(GAME_heur(GAME_getBoard()) == 0) printf("draw");
    else {printf("comp wins");}
}
/*Private interfaces*/

// returns 1 if 'x' wins, -1 if 'o' wins, 0 if no one wins
int GAME_heur(tGAME_BOARD board[SIZE][SIZE]) //tested OK
{

    int i,j;
    char x;
    for( i=0; i<SIZE; i++)
    {
        x = board[i][0];
        for( j=0; j<SIZE; j++)
        {
            if(board[i][j] != x) break ;
            if(j==SIZE-1 && board[i][SIZE-1] == x)
            {
                if(x=='x') return  1;
                if(x=='o') return -1;
            }
        }
    }

    for( i=0; i<SIZE; i++)
    {
        x = board[0][i];
        for( j=0; j<SIZE; j++)
        {
            if(board[j][i] != x) break ;
            if(j== SIZE-1 && board[SIZE-1][i] == x)
            {
                if(x=='x') return  1;
                if(x=='o') return -1;
            }
        }
    }

    return 0;
}

int GAME_isTerminal(tGAME_BOARD board[SIZE][SIZE])
{
    int i,j;
    int heurValue;
    /*check if any of the players win*/
    heurValue = GAME_heur(board);
    if(heurValue == 1 || heurValue == -1 ) return 1;
    /*check for a draw*/
    for( i=0; i<SIZE ; i++)
        for( j=0; j<SIZE; j++)
            if(board[i][j] != 'x' && board[i][j]!= 'o') return 0; //not a terminal

    return 1;
}

void GAME_play(tGAME_BOARD board[SIZE][SIZE], char Xpos, char Ypos, char player)
{
    /*check for invalid inputs*/
    if(player != 'x' && player != 'o' && player !='_') return;
    /*check for invalid coordinates*/
    if(Xpos >= SIZE || Ypos >= SIZE) return;
    board[Ypos][Xpos] = player;
}

void GAME_generateChildren(tNODE *n,tGAME_BOARD board[SIZE][SIZE], char player)
{
    int i,j;
    /*check for terminal state or a terminal node*/
    if((GAME_isTerminal(board)) || ((n->numOfChildren) >= (n->capacity))) return ;

    for( i=0; i<SIZE; i++)
    {
        for( j=0 ; j<SIZE; j++)
        {
            if(board[j][i] == ' ')
            {
                /*Allocate 2d array*/
                int k;
                tGAME_BOARD **newBoard = (tGAME_BOARD**)malloc(SIZE*sizeof(tGAME_BOARD*));
                for( k=0; k<SIZE;k++) newBoard[k] = (tGAME_BOARD*) malloc(SIZE*sizeof(tGAME_BOARD));
                if(newBoard)
                {
                    /*newBoard is a copy of currentBoard*/
                    UTIL_copyState(board,newBoard);
                    /*play at the possible position*/
                    GAME_play(newBoard,i,j,player);
                    /*add the new node to the tree*/
                    TREE_addChild(newBoard,n,n->capacity);
                }
                else printf("\nInside generate children : allocation failed\n");
            }
        }
    }
}

int GAME_AlphaBeta(tNODE *n, int alpha, int beta,int maximizing)
{

    int i;
    if(GAME_isTerminal(n->board) == 1)
    {
        n->data = GAME_heur(n->board);
        return n->data;
    }

    if(maximizing)
    {
        GAME_generateChildren(n,n->board,'x');
        for(i=0; i < (n->numOfChildren); i++)
        {
            alpha = UTIL_max(alpha,GAME_AlphaBeta(n->children[i],alpha,beta,!maximizing));
            #ifdef prune
            if(alpha >= beta){break;}
            #endif // prune
        }
        n->data = alpha;
        return alpha;
    }


    else
    {
        GAME_generateChildren(n,n->board,'o');
        for(i=0; i < n->numOfChildren; i++)
        {
            beta = UTIL_min(beta,GAME_AlphaBeta(n->children[i],alpha,beta,!maximizing));
            #ifdef prune
            if(alpha >= beta) break;
            #endif // prune
        }
        n->data = beta;
        return beta;
    }
}

tNODE*  GAME_getMinHeur(tNODE *parent)
{
    int min = 10000;
    tNODE *minNode = NULL;
#ifdef prune
    if(parent->data == 0 && parent->children[parent->numOfChildren-1]->data == 5) //pruned
    {
        /*Make a clone of the current parent*/
        tNODE *newParent = TREE_createNode(parent->board,parent->capacity);
        /*Destroy current tree*/
        TREE_destroyTree(currentRoot);
        numOfNodes = 0;
        /*Make a new Tree*/
        GAME_AlphaBeta(newParent,-1000,1000,0);
        /*update the new root*/
        currentRoot = newParent;
        parent = newParent;
   }
#endif

    for(int i=0; i < (parent->numOfChildren); i++)
    {
        //printf("\nData = %d\n",parent->children[i]->data);
        if(parent->children[i]->data < min)
        {
            min = parent->children[i]->data;
            minNode = parent->children[i];
        }
    }
    return minNode;
}

tNODE* GAME_findChild(tNODE *parent,tNODE *possibleChild)
{
    for(int i=0; i < (parent->numOfChildren); i++)
    {
        if(UTIL_isEqual(parent->children[i]->board,possibleChild->board))
        {
            free(possibleChild);
            numOfNodes--;
            return (parent->children[i]);
        }
    }
    #ifndef prune
    printf("\nShouldn't be here\nSomething went wrong!\n");
    while(getch());
    #endif // prune


    TREE_destroyTree(currentRoot);
    currentRoot = possibleChild;
    GAME_AlphaBeta(currentRoot,-1000,1000,0);
    return possibleChild;

}

void GAME_printTreeCount(void)
{
    count = 0;
    Tree_countTree(currentNode);
    printf("Count = %d \n",count);

}

