#pragma once

#include "Grid.hpp"
#include "Block.hpp"
#include "SubBlocks.hpp"
#include <memory>


class Game
{
public:
    void handleKeyboardEvents();
    void handleCollisionY();
    void GameLoop();
    void drawGame();
    void blockMoveLeft();
    void blockMoveRight();
    void handleBlockMoveX();
    void handleRotate();
    bool canBlockRotate(bool clockWise, int offsetX = 0);
    void tryRotate(bool isClockWise);
    void getNewBlock();
    void blockMoveDown();
    void clearFinishedRows();
    void hardDrop();



    Game()
    {
        getNewBlock();
    };


private:
    Grid m_grid;
    std::unique_ptr<Block> m_block;
    bool m_isGameOver = false;
    int yPixelsDown = 0;
};