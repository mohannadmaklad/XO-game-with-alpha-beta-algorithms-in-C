#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED
#include "conf.h"

typedef struct node tNODE;
typedef char tGAME_BOARD;

struct node
{
    char data;                 //alpha beta value
    tGAME_BOARD** board;
    char numOfChildren;
    char capacity;
    tNODE **children;
};

typedef enum player {HUMAN,COMPUTER} tPLAYER ;


#endif // TYPE_H_INCLUDED
