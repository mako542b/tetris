#include <Grid.hpp>
#include <raylib.h>
#include <iostream>
#include <Block.hpp>
#include <GameUtils.hpp>

void Grid::draw()
{
    for (int i = Utils::Config::numOfInvRows; i < Utils::Config::numOfRows; i++)
    {
        for (int j = 0; j < Utils::Config::numOfCols; j++)
        {
            BlockID colorIndex = m_cubesGrid[i][j];
            Utils::drawTile(j, i, getBlockColor(colorIndex));
        }
    }
    
}

void Grid::addCube(int posX, int posY, BlockID color)
{
    m_cubesGrid[posY][posX] = color;
}

void Grid::removeCube(int posX, int posY)
{
    m_cubesGrid[posY][posX] = BlockID::EMPTY_CELL;
}

void Grid::addBlock(const Block& block)
{
    auto positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        addCube(position.posX, position.posY, block.m_colorIndex);
    }
}

bool Grid::isCollisionY(const Block& block)
{
    auto positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        if (position.posY + 1 == Utils::Config::numOfRows)
            return true;
        
        if (m_cubesGrid[position.posY + 1][position.posX])
            return true;
    }

    return false;
}

bool Grid::isCollisionXLeft(const Block& block)
{
    auto positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        if ((position.posX - 1) < 0 )
            return true;
        
        if (m_cubesGrid[position.posY][position.posX - 1])
            return true;
    }
    return false;
}

bool Grid::isCollisionXRight(const Block& block)
{
    auto positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        if ((position.posX + 1) >= Utils::Config::numOfCols)
            return true;
        
        if (m_cubesGrid[position.posY][position.posX + 1])
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
}

bool Grid::isRowFinished(int row)
{
    for (int i = 0; i < Utils::Config::numOfCols; i++)
    {
        if (!m_cubesGrid[row][i])
            return false;
    }

    return true;
}

void Grid::handleFullRows()
{
    for (int i = 0; i < Utils::Config::numOfRows; i++)
    {
        if (isRowFinished(i))
        {
            moveRowsDown(i);
        }
    }
}

bool Grid::isCubeAt(int posY, int posX)
{
    return m_cubesGrid[posY][posX];
}

bool Grid::isGameOver(const Block& block)
{
    auto positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        if (m_cubesGrid[position.posY][position.posX])
            return true;
    }
    return false;
}