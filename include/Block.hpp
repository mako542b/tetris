#pragma once

#include <array>
#include <vector>
#include <memory>
#include "Colors.hpp"

class Grid;

class Block
{

friend class Grid;

public:

    virtual ~Block() = default;

    struct position {
        int posY;
        int posX;
    };

    void changeState(bool clockWise);

    void moveY();

    void moveLeft();
    void moveRight();
    std::array<Block::position, 4> getCCWPositions();
    std::array<Block::position, 4> getCWPositions();
    void moveOffset(position offset);
    virtual std::unique_ptr<Block> clone() const = 0;
    const std::array<position, 4> getCurrentPositions() const;
    const std::array<position, 4> getCurrentAbsPositions() const;

    inline bool getIsHardDropped() { return m_isHardDropped; }
    inline void setIsHarddropped() { m_isHardDropped = true; }
    inline void setHarddroppedRows(int rows) { m_hardDroppedRows = rows; }
    inline int getHarddroppedRows() { return m_hardDroppedRows; }
    inline BlockID getBlockID() const { return m_blockID; }


public:

    bool m_isHardDropped = false;
    int m_hardDroppedRows = 0;
    BlockID m_blockID;
    int m_rotationState = 0;

protected:

    int m_offsetX = 5;
    int m_offsetY = 0;
    std::vector<std::array<position, 4>> m_positions;

};