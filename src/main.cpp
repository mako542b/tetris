#include <iostream>
#include <string>

#include "raylib.h"
#include "rlgl.h"
#include "Grid.hpp"
#include "Block.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "Renderer.hpp"

int main()
{
    InitWindow(Config::appWindowSizeX, Config::appWindowSizeY, "Tetris");
    SetTargetFPS(60);
    
    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        game.GameLoop();
        Renderer::Render(game);
        EndDrawing();
    }

    CloseWindow();
}
