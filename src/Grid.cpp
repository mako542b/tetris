#include <Grid.hpp>
#include <raylib.h>
#include <iostream>
#include <Block.hpp>
#include <Colors.hpp>
#include <GameUtils.hpp>

void Grid::draw()
{
    for (int i = 0; i < Utils::Config::numOfRows; i++)
    {
        for (int j = 0; j < Utils::Config::numOfCols; j++)
        {
            int colorIndex = m_cubesGrid[i][j];
            Utils::drawTile(j, i, getBlockColor(colorIndex));
        }
    }
    
}

void Grid::addCube(int posX, int posY, int color)
{
    m_cubesGrid[posY][posX] = color;
}

void Grid::removeCube(int posX, int posY)
{
    m_cubesGrid[posY][posX] = 0;
}

void Grid::addBlock(const Block& block)
{
    auto& positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        addCube(position.posX + block.m_offsetX, position.posY + block.m_offsetY, block.m_colorIndex);
    }
}

bool Grid::isCollisionY(const Block& block)
{
    auto& positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        int posX = position.posX + block.m_offsetX;
        int posY = position.posY + block.m_offsetY + 1;

        if (posY == Utils::Config::numOfRows)
            return true;
        
        if (m_cubesGrid[posY][posX])
            return true;
    }

    return false;
}

bool Grid::isCollisionXLeft(const Block& block)
{
    auto& positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        int posX = position.posX + block.m_offsetX - 1;
        int posY = position.posY + block.m_offsetY;

        if (posX < 0 )
            return true;
        
        if (m_cubesGrid[posY][posX])
            return true;
    }
    return false;
}

bool Grid::isCollisionXRight(const Block& block)
{
    auto& positions = block.getCurrentLayer();

    for (auto& position : positions)
    {
        int posX = position.posX + block.m_offsetX + 1;
        int posY = position.posY + block.m_offsetY;

        if (posX >= Utils::Config::numOfCols)
            return true;
        
        if (m_cubesGrid[posY][posX])
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
