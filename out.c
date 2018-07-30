#include <stdio.h>
#include <stdlib.h>
#include "out.h"
#include "conf.h"
#include "game.h"
#include "type.h"
#include "stdlib.h"

void OUT_clrScreen(void)
{
    system("cls");
}

void OUT_displayBoard(tGAME_BOARD board[][SIZE])
{
    int i,j;
    for( i=0; i<SIZE; i++)
    {
        printf("| ");
        for( j=0; j<SIZE; j++)
        {
            printf("%c",board[i][j]);
            printf(" | ");
        }
        printf("\n");
        printf("\n");
    }
    printf("\n");

}

void OUT_printChildren(tNODE *n)
{
    int i;

    //printf("\nparent data = %d \n",n->data);
    //printf("Heur = %d\n",GAME_heur(n->board));

    for( i=0; i<n->numOfChildren;i++)
    {
        printf("\ndata = %d \n",n->children[i]->data);
        printf("Heur = %d\n",GAME_heur(n->children[i]->board));
        OUT_displayBoard(n->children[i]->board);
    }
    printf("\n");
}

void OUT_displayNodeStatus(void)
{
    printf("Data = %d \n", currentNode->data);
    printf("Children : \n");
    OUT_printChildren(currentNode);
}

