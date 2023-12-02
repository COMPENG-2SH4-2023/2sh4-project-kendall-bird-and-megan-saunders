#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    // no heap member yet - never used new keyword
}


Player::~Player()
{
    // delete any heap members here
    // leave empty for iteration 1
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  

    // where do i get the input? how to check for input?
    // hint 1) not by calling MacUILib_getChar()
    // hint 2) coordinate w team member designing GameMechanism class
    // there will be a method in GameMechanism class that 
    // collectively checks input and store the most recent input. You just need to figure out how to get to it
    // how?? it lies within the GameMechs* inside your private member

    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        
        case 'a':
            if(myDir != LEFT && myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        
        case 's':
            if(myDir != UP && myDir != DOWN)
            {
                myDir = DOWN;
            }
            break;
        
        case 'd':
            if(myDir != LEFT && myDir != RIGHT)
            {
                myDir = RIGHT;
            }
            break;
        
        default:
            break;
    }
       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            playerPos.y--;
            if(playerPos.y <= 0)
            {
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        
        case DOWN:
            playerPos.y++;
            if(playerPos.y >= mainGameMechsRef->getBoardSizeY())
            {
                playerPos.y = playerPos.y = 1;
            }
            break;

        case LEFT:
            playerPos.x--;
            if(playerPos.x <= 0)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX() -2;
            }    
            break;
        
        case RIGHT:
            playerPos.x++;
            if(playerPos.x >= mainGameMechsRef->getBoardSizeX())
            {
                playerPos.x = 1;
            }
            break;
        
        case STOP:
        default:
            break;
    }

}

