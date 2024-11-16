#pragma once

#include <array>
#include <raylib.h>

#define CUSTOM_CYAN CLITERAL(Color){ 0, 255, 255, 255 }

enum BlockID
{
    EMPTY_CELL = 0,
    I_BLOCK,
    O_BLOCK,
    T_BLOCK,
    L_BLOCK,
    J_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    COUNT
};

inline const Color getBlockColor(BlockID block)
{
    switch (block)
    {
        case EMPTY_CELL:
            return DARKBROWN;
        case I_BLOCK:
            return CUSTOM_CYAN;
        case O_BLOCK:
            return YELLOW;
        case T_BLOCK:
            return PURPLE;
        case L_BLOCK:
            return ORANGE;
        case J_BLOCK:
            return BLUE;
        case S_BLOCK:
            return GREEN;
        case Z_BLOCK:
            return RED;
        default:
            return DARKBROWN;
    }
}
