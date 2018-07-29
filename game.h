#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "type.h"
#include "conf.h"

extern tPLAYER currentPlayer;
extern tNODE *currentNode, *tmpNode;


void            GAME_init(void);
tGAME_BOARD**   GAME_getBoard(void);
void            GAME_getBestMove(void);
int             GAME_isGameOver(void);
void            GAME_play(tGAME_BOARD board[SIZE][SIZE], char Xpos, char Ypos, char player);
void            GAME_verifyMove(void);
void            GAME_switchTurns(void);
void            GAME_declareWinner(void);

#endif // GAME_H_INCLUDED
