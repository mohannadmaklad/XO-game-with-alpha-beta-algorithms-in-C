#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "in.h"
#include "conf.h"
#include "type.h"
#include "game.h"
#include "tree.h"

int cursorX , cursorY ;

/*Private interface*/
void IN_updateCursor(void);
void IN_verifyMove(void);
int IN_chek_validity(tGAME_BOARD board[SIZE][SIZE]) {return(board[cursorY][cursorX] == ' ');}
/*If human move is valid, update currentNode*/


void IN_updateCursor(void)
{
    char input;
    input = 'm';
    while (input != 13)
    {
        tGAME_BOARD **buf = GAME_getABuffer();
        /*get input from user*/
        input = getch();

        if( input == 'd' || input == 'D')
        {
            if( cursorX<SIZE-1 ) cursorX++;
            else cursorX = 0;
        }
        if( input == 's' || input == 'S')
        {
            if( cursorY<SIZE-1 ) cursorY++;
            else cursorY = 0;
        }
        if( input == 'a' || input == 'A')
        {
            if( cursorX>0 ) cursorX--;
            else cursorX = SIZE-1;
        }
        if( input == 'w' || input == 'W')
        {
            if (cursorY>0 ) cursorY--;
            else cursorY = SIZE-1;
        }

        system("cls");
        UTIL_copyState(GAME_getBoard(),buf);
        GAME_play(buf,cursorX,cursorY,'_');
        OUT_displayBoard(buf);
    }
}

void IN_verifyMove(void)
{
    tGAME_BOARD **buf = GAME_getABuffer();
    UTIL_copyState(currentNode->board,buf);

    if(IN_chek_validity(buf))
    {
        GAME_play(buf,cursorX,cursorY,'x');
        tmpNode = TREE_createNode(buf,(currentNode->capacity)-1);
        currentNode = GAME_findChild(currentNode,tmpNode);

    }
    else
    {
        GAME_switchTurns();
    }
}


void IN_getHumanMove(void)
{
    IN_updateCursor();
    IN_verifyMove();
}
