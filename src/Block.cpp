#include <Block.hpp>
#include <raylib.h>
#include <GameUtils.hpp>

void Block::changeState(bool clockWise)
{
    m_state = clockWise ? (m_state + 1) % m_positions.size() : (m_state + 3) % m_positions.size();
}


void Block::drawBlock()
{
    auto currentLayer = getCurrentLayer();
    for (auto& cube : currentLayer)
    {
        if (cube.posY < Utils::Config::numOfInvRows)
            return;
            
        Utils::drawTile(cube.posX, cube.posY, getBlockColor(m_colorIndex));
    }
}

const std::array<Block::position, 4> Block::getCurrentLayer() const
{
    auto absPositions = m_positions[m_state];
    for (auto& cube : absPositions)
    {
        cube.posX += m_offsetX;
        cube.posY += m_offsetY;
    }
    return absPositions;
}

const std::array<Block::position, 4>& Block::getPrevLayer()
{   
    int newState = (m_state + 3) % m_positions.size();
    return m_positions[newState];
}

const std::array<Block::position, 4>& Block::getNextLayer()
{   
    int newState = (m_state + 1) % m_positions.size();
    return m_positions[newState];
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

int Block::getOffsetX()
{
    return m_offsetX;
}

int Block::getOffsetY()
{
    return m_offsetY;
}