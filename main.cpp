
#include "Game.h"


bool enemyOnLeftBoundary = false;
bool enemyOnRightBoundary = false;


int main()
{
    

    //Create main window
    Game game;



    // Start the game loop
    while (game.isRunning())
    {
        //Process events
        game.update();

        //clear screen
        game.render();
        
    }

    return 0;
}