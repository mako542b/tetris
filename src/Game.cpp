#include "Game.hpp"
#include <cstdlib>
#include <iostream>

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

bool Game::canBlockRotate(bool clockWise)
{
    auto positions = clockWise ?  m_block->getCWPositions() : m_block->getCCWPositions();

    for (auto& position : positions)
    {
        if (position.posX >= Utils::Config::numOfCols || position.posX < 0 || position.posY < 0)
            return false;
        
        if (m_grid.isTileAt(position.posY, position.posX))
            return false;
    }
    return true;
}

void Game::handleRotate()
{
    if (IsKeyPressed(KEY_X))
    {
        if (canBlockRotate(true))
            m_block->changeState(true);
    }
    else if (IsKeyPressed(KEY_Z))
    {
        if (canBlockRotate(false))
            m_block->changeState(false);
    }

}


void Game::handleKeyboardEvents()
{
    handleBlockMoveX();
}

void Game::handleCollisionY()
{
    if (m_grid.isCollisionY(*m_block))
    {
        m_grid.addBlock(*m_block);
        getNewBlock();
        if (m_grid.isGameOver(*m_block))
        {
            m_isGameOver = true;
        }
    }
}

void Game::drawGame()
{
    m_grid.drawGrid();
    m_block->drawBlock(yPixelsDown);
}


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
        handleKeyboardEvents();
        handleRotate();
        drawGame();
    }
}

void Game::blockMoveLeft()
{
    bool isRowAligned = yPixelsDown < 3;

    if (m_grid.isCollisionLeft(*m_block, isRowAligned))
        return;

    m_block->moveLeft();
}

void Game::blockMoveRight()
{
    bool isRowAligned = yPixelsDown < 3;

    if (m_grid.isCollisionRight(*m_block, isRowAligned))
        return;

    m_block->moveRight();
}

void Game::getNewBlock()
{
    int random = rand() % (BlockID::COUNT - 1) + 1;
    BlockID randomBlockId = static_cast<BlockID>(random);

    switch (randomBlockId)
    {
        case I_BLOCK:
            m_block = std::make_unique<IBlock>();
            break;
        case O_BLOCK:
            m_block = std::make_unique<OBlock>();
            break;
        case T_BLOCK:
            m_block = std::make_unique<TBlock>();
            break;
        case L_BLOCK:
            m_block = std::make_unique<LBlock>();
            break;
        case J_BLOCK:
            m_block = std::make_unique<JBlock>();
            break;
        case S_BLOCK:
            m_block = std::make_unique<SBlock>();
            break;
        case Z_BLOCK:
            m_block = std::make_unique<ZBlock>();
            break;
        default:
            break;
    }
}

void Game::blockMoveDown()
{
    const float interval = (float) 1;
    static float nextMoveDown = interval;

    if(nextMoveDown <= 0 || IsKeyDown(KEY_DOWN))
    {
        m_block->moveY();
        nextMoveDown = interval;
        yPixelsDown = 0;
    }
    else
    {
        nextMoveDown -= GetFrameTime();
        yPixelsDown = static_cast<int>(((interval - nextMoveDown) / interval) * 20);
    }
}

void Game::clearFinishedRows()
{
    m_grid.handleFullRows();
}