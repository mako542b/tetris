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
        handleCollisionY();
        clearFinishedRows();
        blockMoveDown();
        handleBlockMoveX();
        handleRotate();
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

bool Game::canBlockRotate(bool clockWise, int offsetX)
{
    auto positions = clockWise ?  m_currentBlock->getCWPositions() : m_currentBlock->getCCWPositions();

    for (auto position : positions)
    {
        int posX = position.posX + offsetX;

        if (posX >= Utils::Config::numOfCols || posX < 0 || position.posY < 0)
            return false;
        
        if (m_grid.isTileAt(position.posY, posX))
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
    int xOffsets[] = {0, 1, -1, 2, -2};

    for (int offset : xOffsets)
    {
        if (!canBlockRotate(isClockWise, offset))
            continue;

        m_currentBlock->changeState(isClockWise);
        m_currentBlock->moveXOffset(offset);
        return;
    }
}

void Game::handleKeyboardEvents()
{

}

void Game::handleCollisionY()
{
    static float swipeInTimeLeft = 0.1f;

    if (m_grid.isCollisionY(*m_currentBlock))
    {
        if (swipeInTimeLeft > 0)
        {
            swipeInTimeLeft -= GetFrameTime();
            return;
        }

        m_grid.lockBlock(*m_currentBlock);
        getNewBlock();
        swipeInTimeLeft = 0.1f;

        if (m_grid.isGameOver(*m_currentBlock))
        {
            m_isGameOver = true;
        }
    }
}

void Game::handleProjection()
{
    if (m_isProjectionOn)
    {
        std::unique_ptr<Block> projectedBlock = m_currentBlock->clone();
        hardDrop(*projectedBlock);
        projectedBlock->drawProjection();
    }
}

void Game::drawGame()
{
    m_grid.drawGrid();
    m_currentBlock->drawBlock(m_yPixelsDown);
    handleProjection();
    m_nextBlock->drawBlock(80);
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

void Game::hardDrop(Block& block)
{
    while (!m_grid.isCollisionY(block))
    {
        block.moveY();
    }
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

void Game::clearFinishedRows()
{
    m_grid.handleFullRows();
}