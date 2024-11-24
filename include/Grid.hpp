#pragma once

#include <raylib.h>
#include <array>
#include <GameUtils.hpp>
#include <Colors.hpp>

class Block;

class Grid
{

public:
    void addTile(int posX, int posY, BlockID color);
    void removeTile(int posX, int posY);
    void lockBlock(const Block& block);
    bool isCollisionY(const Block& block) const;
    int clearFullRows();
    bool isRowFinished(int row);
    void moveRowsDown(int startRow);
    bool isCollisionLeft(const Block& block, bool rowAligned);
    bool isCollisionRight(const Block& block, bool rowAligned);
    bool isTileAt(int posY, int posX) const;
    bool isGameOver(const Block& block);
    bool isClearedGrid();

    inline BlockID getTileBlockID(int posY, int posX) const { return m_cubesGrid[posY][posX]; }


private:
    static const int numOfColors = 5;

private:
    std::array<std::array<BlockID, Utils::Config::numOfCols>, Utils::Config::numOfRows> m_cubesGrid = {};
};