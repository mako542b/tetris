#pragma once

#include <Block.hpp>

class IBlock : public Block
{
public:
    IBlock()
    {
        m_positions.reserve(2);
        m_positions.push_back({position{0, 0}, position{0, 1}, position{0, 2}, position{0, 3}});
        m_positions.push_back({position{0, 1}, position{1, 1}, position{2, 1}, position{3, 1}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_colorIndex = 1;
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        m_positions.reserve(4);
        m_positions.push_back({position{1, 0}, position{1, 1}, position{0, 1}, position{1, 2}});
        m_positions.push_back({position{0, 0}, position{1, 0}, position{1, 1}, position{2, 0}});
        m_positions.push_back({position{0, 0}, position{0, 1}, position{1, 1}, position{0, 2}});
        m_positions.push_back({position{0, 2}, position{1, 2}, position{1, 1}, position{2, 2}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_colorIndex = 2;
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        m_positions.reserve(1);
        m_positions.push_back({position{0, 0}, position{0, 1}, position{1, 0}, position{1, 1}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_colorIndex = 3;
    }
};