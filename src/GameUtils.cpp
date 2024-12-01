
#include <raylib.h>
#include <GameUtils.hpp>

namespace Utils
{

void drawGameTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY, int height)
{
    if (height <= Config::tilePadding)
        return;

    int totalStartPosY = Config::gamePaddingTop - Config::numOfInvRows * Config::tileSizeY +
        startPosY * Config::tileSizeY + pixelOffsetY + Config::tilePadding;

    DrawRectangle(
        startPosX * Config::tileSizeX + Config::tilePadding + Config::gamePaddingLeft,
        totalStartPosY,
        Config::tileSizeX,// - Config::tilePadding,
        height,// - Config::tilePadding,
        color
    );

    DrawRectangleLines(
        startPosX * Config::tileSizeX + Config::tilePadding + Config::gamePaddingLeft,
        totalStartPosY,
        Config::tileSizeX,
        height,
        Color{50, 50, 50, 100}
    );

}

void drawInfoTile(int startPosX, int startPosY, int xTileCount, const Color& color)
{
    int posY = startPosY * Config::tileSizeY + Config::gamePaddingTop + 80 + Config::tilePadding;
    int posX = startPosX * Config::tileSizeX + Config::gameWindowSizeX + Config::tilePadding +
        Config::infoBoxSizeX / 2 - xTileCount * (Config::tileSizeX / 2);
    
    DrawRectangle(
        posX,
        posY,
        Config::tileSizeX,
        Config::tileSizeY,
        color
    );

    DrawRectangleLines(
        posX,
        posY,
        Config::tileSizeX,
        Config::tileSizeY,
        Color{50, 50, 50, 100}
    );
    
}

}
