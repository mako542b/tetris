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
    static constexpr int paddingYTop = 0;
    static constexpr int paddingYBottom = 0;
    static constexpr int paddingXLeft = 40;
    static constexpr int gameGridSizeX = tileSizeX * numOfCols;
    static constexpr int gameGridSizeY = tileSizeY * (numOfRows - numOfInvRows);
    static constexpr int infoBoxSize = 200;
    static constexpr int gameWindowSizeY = gameGridSizeY + paddingYTop + paddingYBottom;
    static constexpr int gameWindowSizeX = gameGridSizeX + paddingXLeft + infoBoxSize;
};

void drawTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY = 0, int height = Config::tileSizeY);

}
