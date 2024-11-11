#include <iostream>
#include <raylib.h>
#include <rlgl.h>
#include <Grid.hpp>
#include <Block.hpp>
#include <string>
#include <Game.hpp>

int main()
{
    InitWindow(400, 500, "Tetris");
    SetTargetFPS(60);
    
    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);
        
        game.GameLoop();

        EndDrawing();
    }

    CloseWindow();
}
