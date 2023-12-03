#include "GameMechs.h"
#include "MacUILib.h"

// think about where to see the RNG

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20; //default board size
    boardSizeY = 10;

    foodPos.setObjPos(-1, -1, 'o'); // initialize foodPos outside of game board (so to not be displayed)
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX; //default board size
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'o'); // initialize foodPos outside of game board (so to not be displayed)
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();

        if(input == 32)
        {
            exitFlag = true;
            MacUILib_printf("\nGame Over");
        }
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

int GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPos blockOff)
{
    // generate random x and y coord and make sure they are not border or blockOff pos
    // check x and y against 0 and baordSizeX/ Y
    // remember, in objPos class you have an isPosEqual() method.
    // Use this instead of comparing element by element for your convenience

    objPos candPos{0, 0, 'o'};

    do
    {
        candPos.x = rand() % (boardSizeX - 2) + 1;
        candPos.y = rand() % (boardSizeY - 2) + 1;
    }while(candPos.isPosEqual(&blockOff));

    foodPos.setObjPos(candPos);
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}
