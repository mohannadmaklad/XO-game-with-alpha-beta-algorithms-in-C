#include "util.h"
#include "game.h"


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
