#include "util.h"
#include "game.h"
#include <stdlib.h>

int UTIL_isEqual(char board1[SIZE][SIZE],char board2[SIZE][SIZE])
{
    for(int i=0; i<SIZE;i++)
        for(int j=0; j<SIZE;j++)
            if(board1[i][j] != board2[i][j]) return 0;

    return 1;
}

void UTIL_copyState(char src[SIZE][SIZE], char dest[SIZE][SIZE])
{
    int i,j;
    for( i=0; i<SIZE; i++)
        for( j=0; j<SIZE; j++)
            dest[i][j] = src[i][j];
}

int UTIL_max(int a, int b)
{
    if(a>b) return a;
    else return b;
}
int UTIL_min(int a, int b)
{
    if(a<b) return a;
    else return b;
}

tGAME_BOARD**   UTIL_create2dArr(int size)
{
    int k;
    tGAME_BOARD **newBoard = (tGAME_BOARD**) malloc (size*sizeof(tGAME_BOARD*));
    for( k=0; k<SIZE;k++) newBoard[k] = (tGAME_BOARD*) malloc(size*sizeof(tGAME_BOARD));

    return newBoard;
}


void    UTIL_free2dArr(char arr[SIZE][SIZE], int size)
{
        int i;
        for(i=0;i<size;i++)
        {
            if(arr[i]) free(arr[i]);
        }
        if(arr) free(arr);
}
