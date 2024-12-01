#pragma once

#include <raylib.h>

struct Config
{
    static constexpr int tileSizeX = 20;
    static constexpr int tileSizeY = 20;
    static constexpr int numOfCols = 15;
    static constexpr int numOfRows = 23;
    static constexpr int numOfInvRows = 3;
    static constexpr int tilePadding = 1;
    static constexpr int gamePaddingTop = 10;
    static constexpr int gamePaddingBottom = 10;
    static constexpr int gamePaddingLeft = 10;
    static constexpr int gamePaddingRight = 10;
    static constexpr int gameGridSizeX = tileSizeX * numOfCols;
    static constexpr int gameGridSizeY = tileSizeY * (numOfRows - numOfInvRows);
    static constexpr int gameWindowSizeY = gameGridSizeY + gamePaddingBottom + gamePaddingTop;
    static constexpr int gameWindowSizeX = gameGridSizeX + gamePaddingLeft + gamePaddingRight;
    static constexpr int infoBoxSizeX = 150;
    static constexpr int appWindowSizeY = gameGridSizeY + gamePaddingTop + gamePaddingBottom;
    static constexpr int appWindowSizeX = gameWindowSizeX + infoBoxSizeX;
};

namespace Utils
{


void drawGameTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY = 0, int height = Config::tileSizeY);
void drawInfoTile(int startPosX, int startPosY, int xTileCount, const Color& color);

}
