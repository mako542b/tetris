#include <Grid.hpp>
#include <raylib.h>
#include <iostream>
#include <Block.hpp>
#include <GameUtils.hpp>

void Grid::drawGrid()
{
    for (int row = Utils::Config::numOfInvRows; row < Utils::Config::numOfRows; row++)
    {
        for (int col = 0; col < Utils::Config::numOfCols; col++)
        {
            BlockID colorIndex = m_cubesGrid[row][col];
            Utils::drawGameTile(col, row, getBlockColor(colorIndex));
        }
    }
    
}

void Grid::addTile(int posX, int posY, BlockID color)
{
    m_cubesGrid[posY][posX] = color;
}

void Grid::removeTile(int posX, int posY)
{
    m_cubesGrid[posY][posX] = BlockID::EMPTY_CELL;
}

void Grid::lockBlock(const Block& block)
{
    auto positions = block.getCurrentPositions();

    for (auto& position : positions)
    {
        addTile(position.posX, position.posY, block.m_blockID);
    }
}

bool Grid::isCollisionY(const Block& block)
{
    auto positions = block.getCurrentPositions();

    for (auto& position : positions)
    {
        if (position.posY + 1 == Utils::Config::numOfRows)
            return true;
        
        if (isTileAt(position.posY + 1, position.posX))
            return true;
    }

    return false;
}

bool Grid::isCollisionLeft(const Block& block, bool rowAligned)
{
    auto positions = block.getCurrentPositions();

    for (auto& position : positions)
    {
        bool isWallColl = position.posX - 1 < 0;
        bool isCurrentRowColl = isTileAt(position.posY, position.posX - 1);
        bool isNextRowColl = isTileAt(position.posY + 1, position.posX - 1) && !rowAligned;

        if (isWallColl || isCurrentRowColl || isNextRowColl)
            return true;
    }
    return false;
}

bool Grid::isCollisionRight(const Block& block, bool rowAligned)
{
    auto positions = block.getCurrentPositions();

    for (auto& position : positions)
    {
        bool isWallColl = position.posX + 1 >= Utils::Config::numOfCols;
        bool isCurrentRowColl = isTileAt(position.posY, position.posX + 1);
        bool isNextRowColl = isTileAt(position.posY + 1, position.posX + 1) && !rowAligned;

        if (isWallColl || isCurrentRowColl || isNextRowColl)
            return true;
    }
    return false;
}

void Grid::moveRowsDown(int startRow)
{
    for (int row = startRow; row > 0; row--)
    {
        m_cubesGrid[row] = m_cubesGrid[row - 1];
    }
    m_cubesGrid[0] = {};
}

bool Grid::isRowFinished(int row)
{
    for (int col = 0; col < Utils::Config::numOfCols; col++)
    {
        if (!isTileAt(row, col))
            return false;
    }

    return true;
}

int Grid::clearFullRows()
{
    int finishedRows = 0;

    for (int row = 0; row < Utils::Config::numOfRows; row++)
    {
        if (isRowFinished(row))
        {
            moveRowsDown(row);
            finishedRows++;
        }
    }

    return finishedRows;
}

bool Grid::isTileAt(int posY, int posX)
{
    return m_cubesGrid[posY][posX];
}

bool Grid::isGameOver(const Block& block)
{
    auto positions = block.getCurrentPositions();

    for (auto& position : positions)
    {
        if (isTileAt(position.posY, position.posX))
            return true;
    }
    return false;
}

bool Grid::isClearedGrid()
{
    for (int row = 0; row < Utils::Config::numOfRows; row++)
    {
        for (int col = 0; col < Utils::Config::numOfCols; col++)
        {
            if (isTileAt(row, col))
                return false;    
        }
    }
    
    return true;
}
