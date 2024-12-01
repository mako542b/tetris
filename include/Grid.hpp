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
    bool isRowFinished(int row) const;
    void moveRowsDown(int startRow);
    bool isCollisionLeft(const Block& block, bool rowAligned) const;
    bool isCollisionRight(const Block& block, bool rowAligned) const;
    bool isTileAt(int posY, int posX) const;
    bool isGameOver(const Block& block) const;
    bool isClearedGrid() const;

    inline BlockID getTileBlockID(int posY, int posX) const { return m_cubesGrid[posY][posX]; }


private:
    static const int numOfColors = 5;

private:
    std::array<std::array<BlockID, Config::numOfCols>, Config::numOfRows> m_cubesGrid = {};
};