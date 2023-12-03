#include "GameMechs.h"
#include "MacUILib.h"

//defaut constructor for the game mechanics, initalizes the variables & sets board size
GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    //default board size
    boardSizeX = 20;
    boardSizeY = 10;
 
    foodPos.setObjPos(-1, -1, 'o'); // initializes foodPos outside of game board (so it is not displayed)
}
 
//overloaded constructor for the game mechanics with the board parameters being input values
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    //custom board size
    boardSizeX = boardX;
    boardSizeY = boardY;
 
    foodPos.setObjPos(-1, -1, 'o'); // initializes foodPos outside of game board (so it is not displayed)
}
 
//returns exit flag status, self explanatory
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}
 
//sets the exit flag to true, signalling for the program to end
void GameMechs::setExitTrue()
{
    exitFlag = true;
}
 
 
//returns lose flag status, self explanatory
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}
 
//sets loseflag to true, signalling for program to end
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}
 
//returns the current game score
int GameMechs::getScore()
{
    return score;
}
 
//increments the score by one
int GameMechs::incrementScore()
{
    score++;
}
 
//takes in user input & checks for the space key to exit out of the game, returns input
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
 
//sets the input variable with the provided character
void GameMechs::setInput(char this_input)
{
    input = this_input;
}
 
//clears previously stored input
void GameMechs::clearInput()
{
    input = 0;
}
 
//returns horizontal size of game board, self explanatory
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}
 
//returns vertical size of game board, self explanatory
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}
 
//generates a food object with coordinates that don't interfere with the border
//or the snake's body position
void GameMechs::generateFood(objPos blockOff)
{
 
    objPos candPos{0, 0, 'o'};
 
    do
    {
        candPos.x = rand() % (boardSizeX - 2) + 1;
        candPos.y = rand() % (boardSizeY - 2) + 1;
    }while(candPos.isPosEqual(&blockOff));
 
    foodPos.setObjPos(candPos);   
}
 
//returns the current food position
void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}