#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#define SIZE 3
int     UTIL_isEqual(char state1[SIZE][SIZE],char state2[SIZE][SIZE]);
void    UTIL_copyState(char src[SIZE][SIZE], char dest[SIZE][SIZE]);
int     UTIL_max(int a, int b);
int     UTIL_min(int a, int b);



#endif // UTIL_H_INCLUDED
