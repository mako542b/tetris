
#include <raylib.h>
#include <GameUtils.hpp>

namespace Utils
{

void drawTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY, int height)
{
    if (height <= Config::tilePadding)
        return;

    int totalStartPosY = Config::paddingYTop - Config::numOfInvRows * Config::tileSizeY +
        startPosY * Config::tileSizeY + pixelOffsetY + Config::tilePadding;

    DrawRectangle(
        startPosX * Config::tileSizeX + Config::tilePadding,
        totalStartPosY,
        Config::tileSizeX - Config::tilePadding,
        height - Config::tilePadding,
        color
    );

}

}
