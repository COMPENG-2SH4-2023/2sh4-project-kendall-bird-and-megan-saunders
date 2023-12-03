#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    // Set the reference to the GameMechs object
    mainGameMechsRef = thisGMRef;
    // Initialize the player's direction as STOP
    myDir = STOP;

    // Set initial position at the center of the board
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                mainGameMechsRef->getBoardSizeY() / 2, 
                '*');

    // Create a new objPosArrayList for the player's position
    playerPosList = new objPosArrayList();
    
    // Insert the initial position at the head
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // Delete heap members to prevent memory leak
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // Return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    // Process player input and update the player's direction accordingly

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
 
    // Holding the pos information of the current head:
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    
    if(checkSelfCollision())
    {
        // Set lose and exit flags if self-collision detected
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    else
    {
        // Update position based on the current direction
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
    // New head should be inserted to the head of the list:
    playerPosList->insertHead(currentHead);
 
    // then, remove tail:
    playerPosList->removeTail();
    }
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
        // Increase player length and generate new food if collision with food detected
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
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);

    mainGameMechsRef->incrementScore();
}

bool Player::checkSelfCollision()
{
    int arraysize = playerPosList->getSize();
    
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    for (int i = 1; i < arraysize; i++) //start at 1 because head is at position 0
    {
        objPos bodySegment;
        playerPosList->getElement(bodySegment, i);
        
        if (headPos.isPosEqual(&bodySegment))
        {
            return true; // Collision with body detected
        }
    }

    objPos foodPosRef;
    mainGameMechsRef->getFoodPos(foodPosRef);
    
    if (headPos.isPosEqual(&foodPosRef))
    {
        // Collision with food
        increasePlayerLength();
        mainGameMechsRef->generateFood(headPos);
        return false; // No collision with body
    }

    return false; // No collision
}
