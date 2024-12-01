#include "Block.hpp"
#include "raylib.h"
#include "GameUtils.hpp"

void Block::changeState(bool clockWise)
{
    m_rotationState = clockWise ? 
        (m_rotationState + 1) % m_positions.size() :
        (m_rotationState + (m_positions.size() - 1)) % m_positions.size();
}

std::array<Block::position, 4> Block::getCurrentPositions() const
{
    auto positions = m_positions[m_rotationState];
    for (auto& tile : positions)
    {
        tile.posX += m_offsetX;
        tile.posY += m_offsetY;
    }
    return positions;
}

std::array<Block::position, 4> Block::getCurrentAbsPositions() const
{
    return m_positions[m_rotationState];
}

std::array<Block::position, 4> Block::getCCWPositions() const
{   
    int ccwIndex = (m_rotationState + m_positions.size() - 1) % m_positions.size();
    auto ccwPositions = m_positions[ccwIndex];

    for (auto& tile : ccwPositions)
    {
        tile.posX += m_offsetX;
        tile.posY += m_offsetY;
    }

    return ccwPositions;
}

std::array<Block::position, 4> Block::getCWPositions() const
{   
    int cwIndex = (m_rotationState + 1) % m_positions.size();
        auto ccwPositions = m_positions[cwIndex];

    for (auto& tile : ccwPositions)
    {
        tile.posX += m_offsetX;
        tile.posY += m_offsetY;
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

void Block::moveOffset(position offset)
{
    m_offsetX += offset.posX;
    m_offsetY += offset.posY;
}
