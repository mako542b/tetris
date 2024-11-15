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

    void drawBlock();

    void changeState(bool clockWise);

    void moveY();

    void moveLeft();
    void moveRight();
    const std::array<Block::position, 4>& getPrevLayer();
    const std::array<Block::position, 4>& getNextLayer();
    int getOffsetX();
    int getOffsetY();


public:

    BlockID m_colorIndex;

protected:

    int m_offsetX = 5;
    int m_offsetY = 0;
    std::vector<std::array<position, 4>> m_positions;

private:
    const std::array<position, 4> getCurrentLayer() const;
    int m_state = 0;

};