#include "game.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//#define prune  //has problems for now
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
tNODE *currentNode, *tmpNode;

void GAME_init(void)
{
    int i,j;
    for( i=0; i<3;i++)
    {
        for( j=0; j<3;j++)
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
    currentNode = TREE_createTree(initialBoard,SIZE*SIZE);

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
    /*check if any of the players win*/
    if(GAME_heur(board) == 1 || GAME_heur(board) == -1 ) return 1;
    /*check for a draw*/
    for( i=0; i<SIZE ; i++)
        for( j=0; j<SIZE; j++)
            if(board[i][j] != 'x' && board[i][j]!= 'o') return 0;

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
                for( k=0; k<SIZE;k++) newBoard[k] = (char*) malloc(SIZE*sizeof(char));
                /*newBoard is a copy of currentBoard*/
                UTIL_copyState(board,newBoard);
                /*play at the possible position*/
                GAME_play(newBoard,i,j,player);
                /*add the new node to the tree*/
                TREE_addChild(newBoard,n,n->capacity);
            }
        }
    }
}

int GAME_AlphaBeta(tNODE *n, int alpha, int beta,int maximizing)
{
    if(GAME_isTerminal(n->board) == 1)
    {
        n->data = GAME_heur(n->board);
        return n->data;
    }

    if(maximizing)
    {
        GAME_generateChildren(n,n->board,'x');
        for(int i=0; i < n->numOfChildren; i++)
        {
            alpha = UTIL_max(alpha,GAME_AlphaBeta(n->children[i],alpha,beta,!maximizing));
            #ifdef prune
            if(alpha >= beta) break;
            #endif // prune
        }
        n->data = alpha;
        return alpha;
    }


    else
    {
        GAME_generateChildren(n,n->board,'o');
        for(int i=0; i < n->numOfChildren; i++)
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



    if(parent->numOfChildren == 0 )
        GAME_AlphaBeta(parent,-1000,1000,0);

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
            return (parent->children[i]);
        }
    }
    printf("got hereeeeeee");
    while(getch() != 13);
    GAME_AlphaBeta(possibleChild,-1000,1000,0);
    return possibleChild;
}



