#include "Game.h"
#include <exception>
#include <iostream>

#include "Const.h"

int main()
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    try {

        game.run();

    }
    catch (std::exception& e)
    {
        std::cerr << "Error!, halting: " << e.what() << std::endl;
    }

    return 0;
}