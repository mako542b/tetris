
#include <raylib.h>
#include <GameUtils.hpp>

namespace Utils
{

void drawTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY, int height)
{
    if (height <= Config::tilePadding)
        return;

    DrawRectangle(
        startPosX * Config::tileSizeX + Config::tilePadding,
        startPosY * Config::tileSizeY + pixelOffsetY + Config::tilePadding,
        Config::tileSizeX - Config::tilePadding,
        height - Config::tilePadding,
        color
    );

}

}
