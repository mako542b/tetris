
#include <raylib.h>
#include <GameUtils.hpp>

namespace Utils
{

void drawGameTile(int startPosX, int startPosY, const Color& color, int pixelOffsetY, int height)
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

void drawInfoTile(int startPosX, int startPosY, const Color& color)
{
    int posY = startPosY * Utils::Config::tileSizeY + Utils::Config::paddingYTop + 100 + Config::tilePadding;
    int posX = startPosX * Utils::Config::tileSizeX + Utils::Config::gameGridSizeX + 50 + Config::tilePadding;
    
    DrawRectangle(
        posX,
        posY,
        20 - Config::tilePadding,
        20 - Config::tilePadding,
        color
    );
}

}
