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
    void hardDrop(Block& block);
    void handleProjection();

    Game()
    {
        getNewBlock();
    };


private:
    Grid m_grid;
    std::unique_ptr<Block> m_currentBlock;
    std::unique_ptr<Block> m_nextBlock;
    bool m_isGameOver = false;
    int m_yPixelsDown = 0;
    bool m_isProjectionOn = true;
};