// main.cpp

#include "Game.h"
#include "Arena.h"
#include "History.h"
#include "Player.h"
#include "Robot.h"
#include "globals.h"

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}