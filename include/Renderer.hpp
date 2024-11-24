#pragma once

#include "Game.hpp"

class Renderer
{
public:
    void Render(const Game& game);

    void drawCurrentBlock(const Game& game);
    void drawGrid(const Game& game);
    void drawInfo(const Game& game);
    void drawProjection(const Game& game);
    void drawNextBlock(const Game& game);


};