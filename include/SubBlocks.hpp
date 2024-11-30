#pragma once

#include "Block.hpp"
#include "Colors.hpp"

class IBlock : public Block
{
public:
    IBlock()
    {
        m_positions.reserve(2);
        m_positions.push_back({position{1, -1}, position{1, 0}, position{1, 1}, position{1, 2}});
        m_positions.push_back({position{0, 0}, position{1, 0}, position{2, 0}, position{3, 0}});
        m_offsetX = 6;
        m_offsetY = 0;
        m_blockID = BlockID::I_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<IBlock>(*this);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        m_positions.reserve(4);
        m_positions.push_back({position{1, 0}, position{1, 1}, position{0, 1}, position{1, 2}});
        m_positions.push_back({position{0, 1}, position{1, 1}, position{1, 2}, position{2, 1}});
        m_positions.push_back({position{1, 0}, position{1, 1}, position{2, 1}, position{1, 2}});
        m_positions.push_back({position{0, 1}, position{1, 1}, position{1, 0}, position{2, 1}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_blockID = BlockID::T_BLOCK; 
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<TBlock>(*this);
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
        m_blockID = BlockID::O_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<OBlock>(*this);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        m_positions.reserve(2);
        m_positions.push_back({position{0, 0}, position{0, 1}, position{1, 1}, position{1, 2}});
        m_positions.push_back({position{0, 2}, position{1, 2}, position{1, 1}, position{2, 1}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_blockID = BlockID::Z_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<ZBlock>(*this);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        m_positions.reserve(2);
        m_positions.push_back({position{0, 1}, position{0, 2}, position{1, 0}, position{1, 1}});
        m_positions.push_back({position{1, 2}, position{2, 2}, position{0, 1}, position{1, 1}});
        m_offsetX = 5;
        m_offsetY = 0;
        m_blockID = BlockID::S_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<SBlock>(*this);
    }
};

class LBlock : public Block
{
public:
    LBlock()
    {
        m_positions.reserve(4);
        m_positions.push_back({position{0, 1}, position{1, 1}, position{2, 1}, position{2, 0}});  // Rotation 0
        m_positions.push_back({position{1, 0}, position{1, 1}, position{1, 2}, position{2, 2}});  // Rotation 1
        m_positions.push_back({position{0, 1}, position{1, 1}, position{2, 1}, position{0, 2}});  // Rotation 2
        m_positions.push_back({position{1, 0}, position{1, 1}, position{1, 2}, position{0, 0}});  // Rotation 3
        m_offsetX = 5;
        m_offsetY = 0;
        m_blockID = BlockID::L_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<LBlock>(*this);
    }
};

class JBlock : public Block
{
public:
    JBlock()
    {
        m_positions.reserve(4);
        m_positions.push_back({position{0, 0}, position{1, 0}, position{2, 0}, position{2, 1}});  // Rotation 0
        m_positions.push_back({position{1, 0}, position{1, 1}, position{1, 2}, position{2, 0}});  // Rotation 1
        m_positions.push_back({position{0, 0}, position{0, 1}, position{1, 1}, position{2, 1}});  // Rotation 2
        m_positions.push_back({position{0, 2}, position{1, 0}, position{1, 1}, position{1, 2}});  // Rotation 3
        m_offsetX = 5;
        m_offsetY = 0;
        m_blockID = BlockID::J_BLOCK;
    }

    std::unique_ptr<Block> clone() const override
    {
        return std::make_unique<JBlock>(*this);
    }
};

inline std::unique_ptr<Block> getSubBlock(BlockID blockID)
{
    switch (blockID)
    {
        case I_BLOCK:
            return std::make_unique<IBlock>();
        case O_BLOCK:
            return std::make_unique<OBlock>();
        case T_BLOCK:
            return std::make_unique<TBlock>();
        case L_BLOCK:
            return std::make_unique<LBlock>();
        case J_BLOCK:
            return std::make_unique<JBlock>();
        case S_BLOCK:
            return std::make_unique<SBlock>();
        case Z_BLOCK:
            return std::make_unique<ZBlock>();
        default:
            return std::make_unique<IBlock>();
    }
}