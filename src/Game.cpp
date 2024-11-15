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
    auto& positions = clockWise ?  m_block->getNextLayer() : m_block->getPrevLayer();

    for (auto& position : positions)
    {
        int posX = position.posX + m_block->getOffsetX();
        int posY = position.posY + m_block->getOffsetY();

        if (posX >= Utils::Config::numOfCols || posX < 0 || posY < 0)
            return false;
        
        if (m_grid.isCubeAt(posY, posX))
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
    m_grid.draw();
    m_block->drawBlock();
}


void Game::GameLoop()
{

    if (m_isGameOver)
    {
        drawGame();
        DrawText("GAME OVER!", 20, 20, 20, BLACK);
    }
    else
    {
        handleCollisionY();
        m_grid.handleFullRows();
        blockMoveDown();
        handleKeyboardEvents();
        handleRotate();
        drawGame();
    }
}

void Game::blockMoveLeft()
{
    if (m_grid.isCollisionXLeft(*m_block))
        return;

    m_block->moveLeft();
}

void Game::blockMoveRight()
{
    if (m_grid.isCollisionXRight(*m_block))
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
    static float nextMoveDown = 0.1f;

    if(nextMoveDown <= 0 || IsKeyDown(KEY_DOWN))
    {
        m_block->moveY();
        nextMoveDown = 0.1f;
    }
    else
    {
        nextMoveDown -= GetFrameTime();
    }
}