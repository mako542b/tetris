#pragma once

#include "Grid.hpp"
#include "Block.hpp"
#include "SubBlocks.hpp"
#include <memory>
#include "GameData.hpp"

class Game
{
public:
    Game() { getNewBlock(); }
    bool handlePause();
    bool handleCollisionY();
    void GameLoop();
    void blockMoveLeft();
    void blockMoveRight();
    void handleBlockMoveX();
    void handleRotate();
    bool canBlockRotate(bool clockWise, Block::position offsetX = {0, 0}) const;
    void tryRotate(bool isClockWise);
    void getNewBlock();
    void blockMoveDown();
    int handleFinishedRows();
    void setProjectedPosition(Block& block) const;
    void hardDrop(Block& block);
    void handleScore(int finishedRows);
    void handleOptionsInput();
    bool isTSpin() const;
    std::unique_ptr<Block> getProjectedBlock() const;

    inline const Block& getBlock() const { return *m_currentBlock; }
    inline const Block& getNextBlock() const { return *m_nextBlock; }
    inline const Grid& getGrid() const { return m_grid; }
    inline const GameData& getGameData() const { return m_gameData; }
    inline void resetGame() { *this = Game(); }
    inline bool getIsPaused() const { return m_isPaused; }
    inline bool getIsGameOver() const { return m_isGameOver; }
    inline bool getIsProjection() const { return m_isProjection; }

private:
    Grid m_grid;
    std::unique_ptr<Block> m_currentBlock;
    std::unique_ptr<Block> m_nextBlock;
    GameData m_gameData;
    bool m_isGameOver = false;
    bool m_isPaused = false;
    bool m_isProjection = true;
};
