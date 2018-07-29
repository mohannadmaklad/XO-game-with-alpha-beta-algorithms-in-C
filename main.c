#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "type.h"
#include "in.h"
#include "out.h"

int main()
{
    GAME_init();
    while(!GAME_isGameOver())
    {
        OUT_clrScreen();
        OUT_displayBoard(GAME_getBoard());

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

    return 0;
}
