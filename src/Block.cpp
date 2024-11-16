#include <Block.hpp>
#include <raylib.h>
#include <GameUtils.hpp>

void Block::changeState(bool clockWise)
{
    m_rotationState = clockWise ? 
        (m_rotationState + 1) % m_positions.size() :
        (m_rotationState + 3) % m_positions.size();
}


void Block::drawBlock(int pixelsDown)
{
    auto currentLayer = getCurrentPositions();
    for (auto& cube : currentLayer)
    {
        if (cube.posY < Utils::Config::numOfInvRows - 1) //Tile at invisible rows
        {
            continue;
        }
        else if (cube.posY == Utils::Config::numOfInvRows - 1) //First visible row
        {
            Utils::drawTile(cube.posX, cube.posY + 1, getBlockColor(m_colorIndex), 0, pixelsDown);
        }
        else
        {
            Utils::drawTile(cube.posX, cube.posY, getBlockColor(m_colorIndex), pixelsDown);
        }
    }
}

const std::array<Block::position, 4> Block::getCurrentPositions() const
{
    auto positions = m_positions[m_rotationState];
    for (auto& cube : positions)
    {
        cube.posX += m_offsetX;
        cube.posY += m_offsetY;
    }
    return positions;
}

std::array<Block::position, 4> Block::getCCWPositions()
{   
    int ccwIndex = (m_rotationState + m_positions.size() - 1) % m_positions.size();
    auto ccwPositions = m_positions[ccwIndex];

    for (auto& cube : ccwPositions)
    {
        cube.posX += m_offsetX;
        cube.posY += m_offsetY;
    }

    return ccwPositions;
}

std::array<Block::position, 4> Block::getCWPositions()
{   
    int cwIndex = (m_rotationState + 1) % m_positions.size();
        auto ccwPositions = m_positions[cwIndex];

    for (auto& cube : ccwPositions)
    {
        cube.posX += m_offsetX;
        cube.posY += m_offsetY;
    }

    return ccwPositions;
}

void Block::moveY()
{
    m_offsetY++;
}

void Block::moveLeft()
{
    m_offsetX--;
}

void Block::moveRight()
{
    m_offsetX++;
}
