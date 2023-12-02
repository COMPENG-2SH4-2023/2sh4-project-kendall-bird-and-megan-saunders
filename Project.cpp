#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
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

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos); //get player pos

    for(int i=0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j=0; j < myGM->getBoardSizeX(); j++)
        {
            if(i==0 || i == myGM->getBoardSizeY() - 1 || j==0 || j == myGM->getBoardSizeX() - 1)
            {
                printf("%c", '#');
            }
            else if(j == tempPos.x && i == tempPos.y)
            {
                printf("%c", tempPos.symbol);
            }
            else
            {
                printf("%c", ' ');
            }
        }
        printf("\n");
    }
    // Bcus we are using the async input in MacUILib, we have to use MacUILib_printf() instead of cout

    //MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n",
                    //myGM->getScore(),
                    //tempPos.x, tempPos.y);

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
