
#include <raylib.h>
#include <GameUtils.hpp>

namespace Utils
{

void drawTile(int startPosX, int startPosY, const Color& color)
{
    DrawRectangle(
        startPosX * Config::tileSizeX,
        startPosY * Config::tileSizeY,
        Config::tileSizeX,
        Config::tileSizeY,
        color
    );

    DrawRectangleGradientV(
        static_cast<float>(startPosX * Config::tileSizeX),
        static_cast<float>(startPosY * Config::tileSizeY),
        Config::tileSizeX,
        2,
        DARKGRAY,
        color
    );

    DrawRectangleGradientH(
        static_cast<float>(startPosX * Config::tileSizeX),
        static_cast<float>(startPosY * Config::tileSizeY),
        2,
        Config::tileSizeY,
        DARKGRAY,
        color
    );
}

}
