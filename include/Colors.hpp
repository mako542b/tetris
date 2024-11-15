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

inline const Color getBlockColor(BlockID index)
{
    static const std::array<Color, 8> colors = {DARKBROWN, CUSTOM_CYAN, YELLOW, PURPLE, ORANGE, BLUE, GREEN, RED};
    if (index >= colors.size())
        return colors[EMPTY_CELL];
    return colors[index];
}
