#include "Renderer.hpp"
#include <string>

void Renderer::Render(const Game& game)
{
    drawGameWindow(game);
    drawInfoWindow(game);
    handleGameOverWindow(game);
}

void Renderer::handleGameOverWindow(const Game& game)
{
    if (!game.getIsGameOver())
        return;

    constexpr int teksFond = 40;

    const char* text = "Game Over!";
    int tekstLen = MeasureText(text, teksFond);

    DrawRectangle(
        0,
        0,
        Config::gameWindowSizeX,
        Config::gameWindowSizeY,
        Color{200, 200, 200, 50}
    );

    DrawText(
        text,
        (Config::gameWindowSizeX - tekstLen) / 2,
        Config::gameWindowSizeY / 2,
        teksFond,
        BLACK
    );
}

void Renderer::drawGameWindow(const Game& game)
{
    // draw background
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
    const char* score = std::to_string( game.getGameData().getScore()).c_str();

    DrawText("Score:", startPosX - MeasureText("Score:", 20) / 2, startPosY, 20, BLACK);
    DrawText(score, startPosX - MeasureText(score, 20) / 2, startPosY + 30, 20, BLACK);
}

void Renderer::displayLevel(const Game& game)
{
    int startPosX = Config::gameWindowSizeX + Config::infoBoxSizeX / 2;
    int startPosY = Config::gamePaddingTop + 220;
    const char* level = std::to_string( game.getGameData().getLevel()).c_str();

    DrawText("Level:", startPosX - MeasureText("Level:", 20) / 2, startPosY, 20, BLACK);
    DrawText(level, startPosX - MeasureText(level, 20) / 2, startPosY + 30, 20, BLACK);
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
}

void Renderer::drawProjection(const Game& game)
{
    std::unique_ptr<Block> projectedBlock = game.getProjectedBlock();
    auto currentLayer = projectedBlock->getCurrentPositions();
    Color projectionColor = Color{255, 255, 255, 100};

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
