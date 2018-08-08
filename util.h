#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "conf.h"
#include "type.h"


int             UTIL_isEqual(char state1[SIZE][SIZE],char state2[SIZE][SIZE]);
void            UTIL_copyState(char src[SIZE][SIZE], char dest[SIZE][SIZE]);
int             UTIL_max(int a, int b);
int             UTIL_min(int a, int b);
tGAME_BOARD**   UTIL_create2dArr(int size);
void            UTIL_free2dArr(char arr[SIZE][SIZE], int size);


#endif // UTIL_H_INCLUDED
