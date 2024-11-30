#include "Renderer.hpp"
#include <string>

void Renderer::Render(const Game& game)
{
    drawGrid(game);
    drawCurrentBlock(game);
    drawProjection(game);
    drawNextBlock(game);
    drawInfo(game);
}

void Renderer::drawCurrentBlock(const Game& game)
{
    auto& block = game.getBlock();
    auto& gameData = game.getGameData();
    auto currentLayer = block.getCurrentPositions();
    auto color = getBlockColor(block.getBlockID());

    for (auto tile : currentLayer) 
    {
        if (tile.posY < Utils::Config::numOfInvRows - 1) //Tile at invisible rows
        {
            continue;
        }
        else if (tile.posY == Utils::Config::numOfInvRows - 1) //First visible row
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
    for (int row = Utils::Config::numOfInvRows; row < Utils::Config::numOfRows; row++)
    {
        for (int col = 0; col < Utils::Config::numOfCols; col++)
        {
            BlockID colorIndex = game.getGrid().getTileBlockID(row, col);
            Utils::drawGameTile(col, row, getBlockColor(colorIndex));
        }
    }
}

void Renderer::drawNextBlock(const Game& game)
{
    auto& block = game.getNextBlock();
    auto positions = block.getCurrentAbsPositions();

    for (auto pos : positions)
    {
        Utils::drawInfoTile(pos.posX, pos.posY, getBlockColor(block.getBlockID()));
    }
}

void Renderer::drawInfo(const Game& game)
{
    DrawText(std::to_string( game.getGameData().getScore()).c_str(), Utils::Config::gameGridSizeX + 50, Utils::Config::paddingYTop + 300, 20, RED);
}

void Renderer::drawProjection(const Game& game)
{
    std::unique_ptr<Block> projectedBlock = game.getBlock().clone();
    game.setProjectedPosition(*projectedBlock);
    auto currentLayer = projectedBlock->getCurrentPositions();
    Color projectionColor = Color{255, 255, 255, 50};

    for (auto cube : currentLayer)
    {
        if (cube.posY < Utils::Config::numOfInvRows) //Tile at invisible rows
        {
            continue;
        }
        else
        {
            Utils::drawGameTile(cube.posX, cube.posY, projectionColor);
        }
    }
}
