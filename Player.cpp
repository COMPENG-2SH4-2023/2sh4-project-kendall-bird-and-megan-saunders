#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                mainGameMechsRef->getBoardSizeY() / 2, 
                '@');

    // no heap member yet - never used new keyword
    playerPosList = new objPosArrayList();
    playerPosList.insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    // leave empty for iteration 1
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // iteration 3 - get rid of this - returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
    return playerPosList;
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

    objPos currHead; // holding the pos information of the current head
    playerPosList.getHeadElement(currHead);

    switch(myDir)
    {
        case UP:
            currHead.y--;
            if(currHead.y <= 0)
            {
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        
        case DOWN:
            currHead.y++;
            if(currHead.y >= mainGameMechsRef->getBoardSizeY())
            {
                currHead.y = 1;
            }
            break;

        case LEFT:
            currHead.x--;
            if(currHead.x <= 0)
            {
                currHead.x = mainGameMechsRef->getBoardSizeX() -2;
            }    
            break;
        
        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX())
            {
                currHead.x = 1;
            }
            break;
        
        case STOP:
        default:
            break;
    }

}

