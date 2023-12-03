#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                mainGameMechsRef->getBoardSizeY() / 2, 
                '*');

    // no heap member yet - never used new keyword
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
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
 
    objPos currentHead; // holding the pos information of the current head
    playerPosList->getHeadElement(currentHead);
 
    switch(myDir)
    {
        case UP:
            currentHead.y--;
            if(currentHead.y <= 0)
            {
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        
        case DOWN:
            currentHead.y++;
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY())
            {
                currentHead.y = 1;
            }
            break;
 
        case LEFT:
            currentHead.x--;
            if(currentHead.x <= 0)
            {
                currentHead.x = mainGameMechsRef->getBoardSizeX() -2;
            }    
            break;
        
        case RIGHT:
            currentHead.x++;
            if(currentHead.x >= mainGameMechsRef->getBoardSizeX())
            {
                currentHead.x = 1;
            }
            break;
        
        case STOP:
        default:
            break;
    }
 
    if(checkFoodConsumption())
    {
        // Food consumed, no need to remove the tail
    }
    else
    {
    // new current head should be inserted to the head of the list
    playerPosList->insertHead(currentHead);
 
    // then, remove tail
    playerPosList->removeTail();
    }

}

bool Player::checkFoodConsumption()
{
    objPos headPos;
    objPos currentHead;
    objPos foodPosRef;
    mainGameMechsRef->getFoodPos(foodPosRef);
    playerPosList->getHeadElement(currentHead);
    playerPosList->getHeadElement(headPos);
 
    if(headPos.isPosEqual(&foodPosRef))
    {
        increasePlayerLength();
        mainGameMechsRef->generateFood(headPos);
        return true;
    }
    else
    {
        return false;
    }

}

void Player::increasePlayerLength()
{
    // objPos currentHead;
    // playerPosList->getHeadElement(currentHead);

    // objPos newHead = currentHead;
    // playerPosList->insertHead(newHead);

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);

    mainGameMechsRef->incrementScore();
}

bool Player::checkSelfCollision()
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos bodyPart;
        playerPosList->getElement(bodyPart, i);

        if (currentHead.isPosEqual(&bodyPart))
        {
            return true;
        }
    }
    return false;
}

