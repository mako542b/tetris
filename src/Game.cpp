#include "Game.hpp"
#include <cstdlib>

void Game::handleBlockMoveX()
{
    static float nextKeyUpdate = 0.2f;

    if (IsKeyPressed(KEY_LEFT))
    {
        blockMoveLeft();
        nextKeyUpdate = 0.2f;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        if (nextKeyUpdate <= 0.0f)
        {
            blockMoveLeft();
            nextKeyUpdate = 0.05f;
        }
        else
        {
            nextKeyUpdate -= GetFrameTime();
        }
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
        blockMoveRight();
        nextKeyUpdate = 0.2f;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        if (nextKeyUpdate <= 0.0f)
        {
            blockMoveRight();
            nextKeyUpdate = 0.05f;
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

    if (IsKeyDown(KEY_DOWN))
    {
        m_block->moveY();
    }
}

void Game::handleCollisionY()
{
        if (m_grid.isCollisionY(*m_block))
        {
            m_grid.addBlock(*m_block);
            getNewBlock();
        }
}

void Game::drawGame()
{
    m_grid.draw();
    m_block->drawBlock();
}


void Game::GameLoop()
{
    handleCollisionY();
    m_grid.handleFullRows();
    handleKeyboardEvents();
    handleRotate();
    drawGame();
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
    int random = rand() % 3;
    if (random == 0)
        m_block = std::make_unique<TBlock>();
    else if (random == 1)
        m_block = std::make_unique<IBlock>();
    else
        m_block = std::make_unique<OBlock>();
}
