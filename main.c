#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "type.h"
#include "in.h"
#include "out.h"

//#define debug


int main()
{
    GAME_init();
    GAME_printTreeCount();
    TREE_printNumberOfNodes();
    printf("\nUse w,a,s,d for directions\n");
#ifndef debug
    while(getch() != 13);
    while(!GAME_isGameOver())
    {

        OUT_clrScreen();
        OUT_displayBoard(GAME_getBoard());
        TREE_printNumberOfNodes();
        GAME_printTreeCount();
        if(currentPlayer == COMPUTER)
        {
            GAME_getBestMove();
        }
        else
        {
            IN_getHumanMove();
        }

        GAME_switchTurns();
    }

    OUT_clrScreen();
    OUT_displayBoard(GAME_getBoard());
    GAME_declareWinner();
#endif
    return 0;
}
