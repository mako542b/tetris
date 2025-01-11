#include "Game.hpp"
#include <cstdlib>
#include <iostream>
#include "Controllers.hpp"

bool Game::handlePause()
{
    if (Controllers::inputTogglePause())
    {
        m_isPaused = !m_isPaused;
    }

    return m_isPaused;
}

void Game::GameLoop()
{

    if (m_isGameOver)
    {
        if (Controllers::inputNewGame())
        {
            resetGame();
        }

        return;
    }

    if (handlePause())
    {
        return;
    }

    if (handleCollisionY())
    {
        int finishedRows = handleFinishedRows();
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
        handleOptionsInput();
    }
}

void Game::handleOptionsInput()
{
    if (Controllers::inputToggleProjection())
        m_isProjection = !m_isProjection;
}

void Game::handleBlockMoveX()
{
    static float nextKeyUpdate = 0.2f;

    if (Controllers::inputMoveLeftPressed())
    {
        blockMoveLeft();
        nextKeyUpdate = 0.15f;
    }
    else if (Controllers::inputMoveLeftDown())
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
    else if (Controllers::inputMoveRightPressed())
    {
        blockMoveRight();
        nextKeyUpdate = 0.15f;
    }
    else if (Controllers::inputMoveRightDown())
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

bool Game::canBlockRotate(bool clockWise, Block::position offset) const
{
    auto positions = clockWise ?  m_currentBlock->getCWPositions() : m_currentBlock->getCCWPositions();

    for (auto position : positions)
    {
        int posX = position.posX + offset.posX;
        int posY = position.posY + offset.posY;

        if (posX >= Config::numOfCols || posX < 0 || position.posY >= Config::numOfRows)
            return false;
        
        if (m_grid.isTileAt(posY, posX))
            return false;
    }
    return true;
}

void Game::handleRotate()
{
    if (Controllers::inputRotateCW())
    {
        tryRotate(true);
    }
    else if (Controllers::inputRotateCCW())
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

void Game::blockMoveLeft()
{
    bool isTileRowAligned = m_gameData.getBlockRowPixelOffset() < 3;

    if (m_grid.isCollisionLeft(*m_currentBlock, isTileRowAligned))
        return;

    m_currentBlock->moveLeft();
}

void Game::blockMoveRight()
{
    bool isTileRowAligned = m_gameData.getBlockRowPixelOffset() < 3;

    if (m_grid.isCollisionRight(*m_currentBlock, isTileRowAligned))
        return;

    m_currentBlock->moveRight();
}

void Game::getNewBlock()
{
    int random = GetRandomValue(1, BlockID::COUNT - 1);
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

void Game::setProjectedPosition(Block& block) const
{
    while (!m_grid.isCollisionY(block))
    {
        block.moveY();
    }
}

std::unique_ptr<Block> Game::getProjectedBlock() const
{
    std::unique_ptr<Block> projectedBlock = getBlock().clone();
    setProjectedPosition(*projectedBlock);
    return projectedBlock;
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

    if (m_grid.isCollisionY(*m_currentBlock))
        return;

    if (Controllers::inputHardDrop())
    {
        hardDrop(*m_currentBlock);
        m_gameData.resetNextGravityMove();
    }
    else if(m_gameData.getNextGravityMove() <= 0 || Controllers::inputMoveDown())
    {
        m_currentBlock->moveY();
        m_gameData.resetNextGravityMove();
    }
    else
    {
        m_gameData.updateNextGravityMove();
    }
}

int Game::handleFinishedRows()
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
    m_gameData.handleScore(info);
}

bool Game::isTSpin() const
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

            if (cornerYPos >= Config::numOfRows ||
                cornerXPos < 0 ||
                cornerXPos >= Config::numOfCols||
                m_grid.isTileAt(cornerYPos, cornerXPos
            ))
                occupiedCorners++;
        }
    }

    return occupiedCorners >= 3;
}
