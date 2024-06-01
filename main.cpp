#include "Game.h"


int main()
{
    srand(static_cast<unsigned>(time(0)));

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