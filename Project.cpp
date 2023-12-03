#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM; //pointer to GameMechanics
Player* myPlayer; //pointer to Player

//function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    myGM = new GameMechs(26, 13); // sets board size to 26x13
    myPlayer = new Player(myGM); //creates player instance

    objPos tempPos{-1, -1, 'o'};
    myGM->generateFood(tempPos); //generates initial food position
}

void GetInput(void)
{
   myGM->getInput(); //references game mechanics to get user input
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //updates player direction based on input
    myPlayer->movePlayer(); 

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
  
    objPos tempFoodPos;
    myGM->getFoodPos(tempFoodPos);

    for(int i=0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j=0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            // iterates through every element in the player's body list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;
            // if player body was drawn, don't draw anything below

            if(i==0 || i == myGM->getBoardSizeY() - 1 || j==0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#'); //prints borders
            }
            else if(j == tempFoodPos.x && i == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.symbol); //prints food
            }
            else
            {
                MacUILib_printf("%c", ' '); //prints empty space
            }
        }
        printf("\n");
    }
    // b/c we are using the async input in MacUILib, we have to use MacUILib_printf() instead of cout

    if (myGM->getLoseFlagStatus()) //message for if game is lost
    {
        MacUILib_clearScreen();
        MacUILib_printf("Good Try! You lost!\n");
    }
    else if (myGM->getExitFlagStatus()) //message for if game is exited, NOT lost
    {
        MacUILib_clearScreen();
        MacUILib_printf("You have exited the game!\n");
    }
    else
    {
        MacUILib_printf("Score: %d\n", myGM->getScore()); //prints player's score
        MacUILib_printf("Press SPACE to exit.");
    }

    //MacUILib_printf("Food Pos: <%d,%d>\n", tempFoodPos.x, tempFoodPos.y);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{  
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
