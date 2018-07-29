#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED
#include "conf.h"

typedef struct node tNODE;
typedef char tGAME_BOARD;

struct node
{
    int data;                 //alpha beta value
    tGAME_BOARD** board;
    int numOfChildren;
    int capacity;
    tNODE **children;
};

typedef enum player {HUMAN,COMPUTER} tPLAYER ;


#endif // TYPE_H_INCLUDED
