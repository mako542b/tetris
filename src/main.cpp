#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <Grid.hpp>
#include <Block.hpp>
#include <string>
#include <Game.hpp>
#include "GameUtils.hpp"

int main()
{
    InitWindow(Utils::Config::gameWindowSizeX, Utils::Config::gameWindowSizeY, "Tetris");
    SetTargetFPS(60);
    
    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        
        game.GameLoop();

        EndDrawing();
    }

    CloseWindow();
}
