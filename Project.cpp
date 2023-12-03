#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

// OOD Benefit - very limited global var declaration
// In advanced OOD, don't even need global variable
GameMechs* myGM;
Player* myPlayer;

// objPos myPos; (he wrote then deleted this - may need to uncomment)

//bool exitFlag; (he deleted this in vid)

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
    
    myGM = new GameMechs(26, 13); // make board size 26x13
    myPlayer = new Player(myGM);

    // Think about when to generate the new food
    // Think about whether you want to set up a debug key to call the food generation routine for verification
    // remember, generate food requires player reference. You will need to provide it after player object is instantiated
    // this is a makeshift setup so i dont have to touch generateItem yet
    // you need to do this yourself 
    objPos tempPos{-1, -1, 'o'}; // REMOVE this in future steps
    myGM->generateFood(tempPos);
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
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
            // iterate thru every element in the list
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
            // if player body was drawn, don't draw anything below.

            if(i==0 || i == myGM->getBoardSizeY() - 1 || j==0 || j == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            else if(j == tempFoodPos.x && i == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        printf("\n");
    }
    // Bcus we are using the async input in MacUILib, we have to use MacUILib_printf() instead of cout

    MacUILib_printf("Score: %d\n", myGM->getScore());

    //MacUILib_printf("Food Pos: <%d,%d>\n", tempFoodPos.x, tempFoodPos.y);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
