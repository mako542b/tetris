#pragma once

#include "Grid.hpp"
#include "Block.hpp"
#include "SubBlocks.hpp"
#include <memory>
#include "InfoWindow.hpp"

enum class TSpinType
{
    NONE = 0,
    MINI,
    CLASSIC,
    TRIPLE
};

class Game
{
public:
    void handleKeyboardEvents();
    bool handleCollisionY();
    void GameLoop();
    void drawGame();
    void blockMoveLeft();
    void blockMoveRight();
    void handleBlockMoveX();
    void handleRotate();
    bool canBlockRotate(bool clockWise, Block::position offsetX = {0, 0});
    void tryRotate(bool isClockWise);
    void getNewBlock();
    void blockMoveDown();
    int checkFinishedRows();
    void setProjectedPosition(Block& block);
    void hardDrop(Block& block);
    void handleProjection();
    void handleScore(int finishedRows);
    bool isTSpin();


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
    InfoWindow m_infoWindow;
};