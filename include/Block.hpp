#pragma once

#include <array>
#include <vector>
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

    void drawBlock(int pixelsDown);

    void changeState(bool clockWise);

    void moveY();

    void moveLeft();
    void moveRight();
    std::array<Block::position, 4> getCCWPositions();
    std::array<Block::position, 4> getCWPositions();
    int getOffsetX();
    int getOffsetY();


public:

    BlockID m_colorIndex;

protected:

    int m_offsetX = 5;
    int m_offsetY = 0;
    std::vector<std::array<position, 4>> m_positions;

private:
    const std::array<position, 4> getCurrentPositions() const;
    int m_rotationState = 0;

};