#pragma once

#include <raylib.h>
#include <array>
#include <GameUtils.hpp>
#include <Colors.hpp>

class Block;

class Grid
{

public:
    void drawGrid();
    void addTile(int posX, int posY, BlockID color);
    void removeTile(int posX, int posY);
    void lockBlock(const Block& block);
    bool isCollisionY(const Block& block);
    int clearFullRows();
    bool isRowFinished(int row);
    void moveRowsDown(int startRow);
    bool isCollisionLeft(const Block& block, bool rowAligned);
    bool isCollisionRight(const Block& block, bool rowAligned);
    bool isTileAt(int posY, int posX);
    bool isGameOver(const Block& block);
    bool isClearedGrid();


private:
    static const int numOfColors = 5;

private:
    std::array<std::array<BlockID, Utils::Config::numOfCols>, Utils::Config::numOfRows> m_cubesGrid = {};
};