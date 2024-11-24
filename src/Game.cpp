#include "Game.hpp"
#include <cstdlib>
#include <iostream>

void Game::GameLoop()
{

    if (m_isGameOver)
    {
        drawGame();
        DrawText("GAME OVER!", 20, 20, 20, BLACK);

        if (IsKeyDown(KEY_N))
        {
            m_grid = {};
            m_isGameOver = false;
        }
    }
    else
    {
        if (handleCollisionY())
        {
            int finishedRows = checkFinishedRows();
            handleScore(finishedRows);
            getNewBlock();

            if (m_grid.isGameOver(*m_currentBlock))
            {
                m_isGameOver = true;
            }
        }
        else
        {
            blockMoveDown();
            handleBlockMoveX();
            handleRotate();
        }

        drawGame();
    }
}

void Game::handleBlockMoveX()
{
    static float nextKeyUpdate = 0.2f;

    if (IsKeyPressed(KEY_LEFT))
    {
        blockMoveLeft();
        nextKeyUpdate = 0.15f;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        if (nextKeyUpdate <= 0.0f)
        {
            blockMoveLeft();
            nextKeyUpdate = 0.005f;
        }
        else
        {
            nextKeyUpdate -= GetFrameTime();
        }
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
        blockMoveRight();
        nextKeyUpdate = 0.15f;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        if (nextKeyUpdate <= 0.0f)
        {
            blockMoveRight();
            nextKeyUpdate = 0.005f;
        }
        else
        {
            nextKeyUpdate -= GetFrameTime();
        }
    }
}

bool Game::canBlockRotate(bool clockWise, Block::position offset)
{
    auto positions = clockWise ?  m_currentBlock->getCWPositions() : m_currentBlock->getCCWPositions();

    for (auto position : positions)
    {
        int posX = position.posX + offset.posX;
        int posY = position.posY + offset.posY;

        if (posX >= Utils::Config::numOfCols || posX < 0 || position.posY >= Utils::Config::numOfRows)
            return false;
        
        if (m_grid.isTileAt(posY, posX))
            return false;
    }
    return true;
}

void Game::handleRotate()
{
    if (IsKeyPressed(KEY_X))
    {
        tryRotate(true);
    }
    else if (IsKeyPressed(KEY_Z))
    {
        tryRotate(false);
    }
}

void Game::tryRotate(bool isClockWise)
{
    Block::position xOffsets[] = { {0, 0}, {0, 1}, {0, -1}, {0, 2}, {0,-2} , {1, 0}, {1, 1}, {1, -1}};

    for (auto offset : xOffsets)
    {
        if (!canBlockRotate(isClockWise, offset))
            continue;

        m_currentBlock->changeState(isClockWise);
        m_currentBlock->moveOffset(offset);
        return;
    }
}

void Game::handleKeyboardEvents()
{

}

bool Game::handleCollisionY()
{
    static float swipeInTimeLeft = 0.1f;

    if (m_grid.isCollisionY(*m_currentBlock))
    {
        if (swipeInTimeLeft > 0 && !m_currentBlock->getIsHardDropped())
        {
            swipeInTimeLeft -= GetFrameTime();
            return false;
        }

        m_grid.lockBlock(*m_currentBlock);
        swipeInTimeLeft = 0.1f;

        return true;
    }

    return false;
}

void Game::handleProjection()
{
    if (m_isProjectionOn)
    {
        std::unique_ptr<Block> projectedBlock = m_currentBlock->clone();
        setProjectedPosition(*projectedBlock);
        projectedBlock->drawProjection();
    }
}

void Game::drawGame()
{
    m_grid.drawGrid();
    m_currentBlock->drawBlock(m_yPixelsDown);
    handleProjection();

    m_infoWindow.drawNextBlock(*m_nextBlock);
    m_infoWindow.drawScore();
}

void Game::blockMoveLeft()
{
    bool isTileRowAligned = m_yPixelsDown < 3;

    if (m_grid.isCollisionLeft(*m_currentBlock, isTileRowAligned))
        return;

    m_currentBlock->moveLeft();
}

void Game::blockMoveRight()
{
    bool isTileRowAligned = m_yPixelsDown < 3;

    if (m_grid.isCollisionRight(*m_currentBlock, isTileRowAligned))
        return;

    m_currentBlock->moveRight();
}

void Game::getNewBlock()
{
    int random = rand() % (BlockID::COUNT - 1) + 1;
    BlockID randomBlockId = static_cast<BlockID>(random);

    if (!m_nextBlock)
    {
        m_currentBlock = getSubBlock(randomBlockId);
        random = rand() % (BlockID::COUNT - 1) + 1;
        randomBlockId = static_cast<BlockID>(random);
    }
    else
    {
        m_currentBlock = std::move(m_nextBlock);
    }

    m_nextBlock = getSubBlock(randomBlockId);
}

void Game::setProjectedPosition(Block& block)
{
    while (!m_grid.isCollisionY(block))
    {
        block.moveY();
    }
}

void Game::hardDrop(Block& block)
{
    int hardDroppedRows = 0;

    while (!m_grid.isCollisionY(block))
    {
        block.moveY();
        hardDroppedRows++;
    }

    m_currentBlock->setHarddroppedRows(hardDroppedRows);
    m_currentBlock->setIsHarddropped();
}

void Game::blockMoveDown()
{
    const float interval = (float) .2;
    static float nextMoveDown = interval;

    if (m_grid.isCollisionY(*m_currentBlock))
        return;

    if (IsKeyPressed(KEY_SPACE))
    {
        hardDrop(*m_currentBlock);
        nextMoveDown = interval;
        m_yPixelsDown = 0;
    }
    else if(nextMoveDown <= 0 || IsKeyDown(KEY_DOWN))
    {
        m_currentBlock->moveY();
        nextMoveDown = interval;
        m_yPixelsDown = 0;
    }
    else
    {
        nextMoveDown -= GetFrameTime();
        m_yPixelsDown = static_cast<int>(((interval - nextMoveDown) / interval) * 20);
    }
}

int Game::checkFinishedRows()
{
    return m_grid.clearFullRows();
}

void Game::handleScore(int finishedRows)
{
    ScoreInfo_t info;
    info.clearedRows = finishedRows;
    info.hardDroppedRows = m_currentBlock->getHarddroppedRows();
    info.isGridCleared = m_grid.isClearedGrid();
    info.isTSpin = isTSpin();
    m_infoWindow.handleScore(info);
}

bool Game::isTSpin()
{
    if (m_currentBlock->m_blockID != BlockID::T_BLOCK || m_currentBlock->m_rotationState != 2)
        return false;

    auto pivot = m_currentBlock->getCurrentPositions()[1];
    int pivotOffsetsY[] = {-1, 1};
    int pivotOffsetsX[] = {-1, 1};
    int occupiedCorners = 0;

    for (int offsetsY : pivotOffsetsY)
    {
        for (int offsetsX : pivotOffsetsX)
        {
            int cornerYPos = pivot.posY + offsetsY;
            int cornerXPos = pivot.posX + offsetsX;

            if (cornerYPos >= Utils::Config::numOfRows ||
                cornerXPos < 0 ||
                cornerXPos >= Utils::Config::numOfCols||
                m_grid.isTileAt(cornerYPos, cornerXPos
            ))
                occupiedCorners++;
        }
    }

    return occupiedCorners >= 3;

}