#pragma once

#include "Game.hpp"

class Renderer
{
public:
    static void Render(const Game& game);
    static void drawGameWindow(const Game& game);
    static void drawInfoWindow(const Game& game);
    static void drawCurrentBlock(const Game& game);
    static void drawGrid(const Game& game);
    static void drawProjection(const Game& game);
    static void drawNextBlock(const Game& game);
    static void displayScore(const Game& game);
    static void displayLevel(const Game& game);
    static void handleGameOverWindow(const Game& game);
};
