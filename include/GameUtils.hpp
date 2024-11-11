#pragma once

#include <raylib.h>

namespace Utils
{

struct Config
{
    static constexpr int tileSizeX = 20;
    static constexpr int tileSizeY = 20;
    static constexpr int numOfCols = 15;
    static constexpr int numOfRows = 25;
    static constexpr int boardSizeX = tileSizeX * numOfCols;
    static constexpr int boardSizeY = tileSizeY * numOfRows;
};

void drawTile(int startPosY, int startPosX, const Color& color);

}
