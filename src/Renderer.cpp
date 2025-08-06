#include "Renderer.hpp"
#include <string>

#define GET_ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

void Renderer::Render(const Game& game)
{
    ClearBackground(DARKGRAY);
    drawGameWindow(game);
    drawInfoWindow(game);
    handleGameOverWindow(game);
    handleDisplayOptions(game);
}

void Renderer::handleDisplayOptions(const Game& game)
{
    if (!game.getIsPaused())
        return;

    const int tekstStartPosY = 50;
    const int textSize = 25;
    const int textLineDistY = textSize + 10;

    const char* text1 = "OPTIONS:";
    const char* text2 = "SIDE ARROWS: move sideway";
    const char* text3 = "ARROW DOWN: soft drop";
    const char* text4 = "P: toggle projection";
    const char* text5 = "Z: rotate anti-clockwise";
    const char* text6 = "x: rotate clockwise";
    const char* text7 = "SPACE: hard drop";
    const char* text8 = "O: resume";

    int text1Len = MeasureText(text1, textSize);
    int text2Len = MeasureText(text2, textSize);
    int text3Len = MeasureText(text3, textSize);
    int text4Len = MeasureText(text4, textSize);
    int text5Len = MeasureText(text5, textSize);
    int text6Len = MeasureText(text6, textSize);
    int text7Len = MeasureText(text7, textSize);
    int text8Len = MeasureText(text8, textSize);

    const char* textArray[] = {text1, text2, text3, text4, text5, text6, text7, text8};
    const int textLenArray[] = {text1Len, text2Len, text3Len, text4Len, text5Len, text6Len, text7Len, text8Len};

    DrawRectangle(
        0,
        0,
        Config::appWindowSizeX,
        Config::appWindowSizeY,
        Color{255, 160, 0, 200}
    );

    for (int i = 0; i < GET_ARRAY_SIZE(textArray) && i < GET_ARRAY_SIZE(textLenArray); i++)
    {
        DrawText(
            textArray[i],
            (Config::appWindowSizeX - textLenArray[i]) / 2,
            tekstStartPosY + textLineDistY * i,
            textSize,
            BLACK
        );
    }
}

void Renderer::handleGameOverWindow(const Game& game)
{
    if (!game.getIsGameOver())
        return;

    constexpr int text1Fond = 40;
    constexpr int text2Fond = 25;

    const char* text1 = "Game Over!";
    const char* text2 = "press n to restart";
    int text1Len = MeasureText(text1, text1Fond);
    int text2Len = MeasureText(text2, text2Fond);

    DrawRectangle(
        0,
        0,
        Config::gameWindowSizeX,
        Config::gameWindowSizeY,
        Color{200, 200, 200, 50}
    );

    DrawText(
        text1,
        (Config::gameWindowSizeX - text1Len) / 2,
        Config::gameWindowSizeY / 2 - text1Fond,
        text1Fond,
        BLACK
    );

        DrawText(
        text2,
        (Config::gameWindowSizeX - text2Len) / 2,
        Config::gameWindowSizeY / 2,
        text2Fond,
        BLACK
    );
}

void Renderer::drawGameWindow(const Game& game)
{
    DrawRectangle(0, 0, Config::gameWindowSizeX, Config::gameWindowSizeY, CLITERAL(Color){0, 0, 0, 150});
    drawGrid(game);
    drawProjection(game);
    drawCurrentBlock(game);
}

void Renderer::drawNextBlock(const Game& game)
{
    int textWidth = MeasureText("Next", 20);
    int textStartX = Config::gameWindowSizeX + Config::infoBoxSizeX / 2 - textWidth / 2;
    int textStartY = Config::gamePaddingTop + 40 + Config::tilePadding;
    DrawText("Next:", textStartX, textStartY, 20, BLACK);

    auto& block = game.getNextBlock();
    auto positions = block.getCurrentAbsPositions();
    int xTileCount = 1;

    for (auto pos : positions)
    {
        if (pos.posX + 1 > xTileCount)
            xTileCount = pos.posX + 1;
    }

    for (auto pos : positions)
    {
        Utils::drawInfoTile(pos.posX, pos.posY, xTileCount, getBlockColor(block.getBlockID()));
    }
}

void Renderer::displayScore(const Game& game)
{
    int startPosX = Config::gameWindowSizeX + Config::infoBoxSizeX / 2;
    int startPosY = Config::gamePaddingTop + 150;

    std::string scoreStr = std::to_string(game.getGameData().getScore());
    const char* score = scoreStr.c_str();

    DrawText("Score:", startPosX - MeasureText("Score:", 20) / 2, startPosY, 20, BLACK);
    DrawText(score, startPosX - MeasureText(score, 20) / 2, startPosY + 30, 20, BLACK);
}

void Renderer::displayLevel(const Game& game)
{
    int startPosX = Config::gameWindowSizeX + Config::infoBoxSizeX / 2;
    int startPosY = Config::gamePaddingTop + 220;
    std::string levelStr = std::to_string(game.getGameData().getLevel());
    const char* level = levelStr.c_str();

    DrawText("Level:", startPosX - MeasureText("Level:", 20) / 2, startPosY, 20, BLACK);
    DrawText(level, startPosX - MeasureText(level, 20) / 2, startPosY + 30, 20, BLACK);
}

void Renderer::optionsButtonInfo()
{
    int startPosX = Config::gameWindowSizeX + Config::infoBoxSizeX / 2;
    int startPosY = Config::gamePaddingTop + 300;
    int fontSize = 15;
    const char* text = "opt/pause: O";
    DrawText("opt/pause: O", startPosX - MeasureText(text, fontSize) / 2, startPosY, fontSize, BLACK);
}

void Renderer::drawCurrentBlock(const Game& game)
{
    auto& block = game.getBlock();
    auto& gameData = game.getGameData();
    auto currentLayer = block.getCurrentPositions();
    auto color = getBlockColor(block.getBlockID());

    for (auto tile : currentLayer) 
    {
        if (tile.posY < Config::numOfInvRows - 1) //Tile at invisible rows
        {
            continue;
        }
        else if (tile.posY == Config::numOfInvRows - 1) //First visible row
        {
            Utils::drawGameTile(tile.posX, tile.posY + 1, color, 0, gameData.getBlockRowPixelOffset());
        }
        else
        {
            Utils::drawGameTile(tile.posX, tile.posY, color, gameData.getBlockRowPixelOffset());
        }
    }
}

void Renderer::drawGrid(const Game& game)
{
    for (int row = Config::numOfInvRows; row < Config::numOfRows; row++)
    {
        for (int col = 0; col < Config::numOfCols; col++)
        {
            BlockID colorIndex = game.getGrid().getTileBlockID(row, col);
            Utils::drawGameTile(col, row, getBlockColor(colorIndex));
        }
    }
}

void Renderer::drawInfoWindow(const Game& game)
{
    DrawRectangle(Config::gameWindowSizeX, 0, Config::infoBoxSizeX, Config::gameWindowSizeY, Color{ 255, 161, 0, 100 });
    drawNextBlock(game);
    displayScore(game);
    displayLevel(game);
    optionsButtonInfo();
}

void Renderer::drawProjection(const Game& game)
{
    if (!game.getIsProjection())
        return;

    std::unique_ptr<Block> projectedBlock = game.getProjectedBlock();
    auto currentLayer = projectedBlock->getCurrentPositions();
    Color projectionColor = Color{255, 255, 200, 40};

    for (auto cube : currentLayer)
    {
        if (cube.posY < Config::numOfInvRows) //Tile at invisible rows
        {
            continue;
        }
        else
        {
            Utils::drawGameTile(cube.posX, cube.posY, projectionColor);
        }
    }
}
