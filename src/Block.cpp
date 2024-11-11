#include <Block.hpp>
#include <raylib.h>
#include <Colors.hpp>
#include <GameUtils.hpp>

Block::Block()
{
    m_colorIndex = 3;
}

void Block::changeState(bool clockWise)
{
    m_state = clockWise ? (m_state + 1) % m_positions.size() : (m_state + 3) % m_positions.size();
}


void Block::drawBlock()
{
    auto& currentLayer = getCurrentLayer();
    for (auto& cube : currentLayer)
    {
        Utils::drawTile(m_offsetX + cube.posX, m_offsetY + cube.posY, getBlockColor(m_colorIndex));
    }
}

const std::array<Block::position, 4>& Block::getCurrentLayer() const
{
    return m_positions[m_state];
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