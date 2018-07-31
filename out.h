#ifndef OUT_H_INCLUDED
#define OUT_H_INCLUDED
#include "type.h"
#include "conf.h"
//
//Public Interface
//
void OUT_clrScreen(void);
void OUT_displayBoard(tGAME_BOARD board[][SIZE]);
void OUT_printChildren(tNODE *n);



#endif // OUT_H_INCLUDED
