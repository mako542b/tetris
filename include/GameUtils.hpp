#pragma once

#include <raylib.h>

namespace Utils
{

struct Config
{
    static constexpr int tileSizeX = 20;
    static constexpr int tileSizeY = 20;
    static constexpr int numOfCols = 15;
    static constexpr int numOfRows = 23;
    static constexpr int numOfInvRows = 3;
    static constexpr int tilePadding = 1;
    static constexpr int boardSizeX = tileSizeX * numOfCols;
    static constexpr int boardSizeY = tileSizeY * numOfRows;
};

void drawTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY = 0, int height = Config::tileSizeY);

}
