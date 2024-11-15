#pragma once

#include <raylib.h>
#include <array>
#include <GameUtils.hpp>
#include <Colors.hpp>

class Block;

class Grid
{

public:
    void draw();
    void addCube(int posX, int posY, BlockID color);
    void removeCube(int posX, int posY);
    void addBlock(const Block& block);
    bool isCollisionY(const Block& block);
    void handleFullRows();
    bool isRowFinished(int row);
    void moveRowsDown(int startRow);
    bool isCollisionXLeft(const Block& block);
    bool isCollisionXRight(const Block& block);
    bool isCubeAt(int posY, int posX);
    bool isGameOver(const Block& block);


private:
    static const int numOfColors = 5;

private:
    std::array<std::array<BlockID, Utils::Config::numOfCols>, Utils::Config::numOfRows> m_cubesGrid = {};
};