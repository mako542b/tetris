#pragma once

#include "Grid.hpp"
#include "Block.hpp"
#include "SubBlocks.hpp"
#include <memory>
#include "GameData.hpp"

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
    bool handleCollisionY();
    void GameLoop();
    void blockMoveLeft();
    void blockMoveRight();
    void handleBlockMoveX();
    void handleRotate();
    bool canBlockRotate(bool clockWise, Block::position offsetX = {0, 0});
    void tryRotate(bool isClockWise);
    void getNewBlock();
    void blockMoveDown();
    int checkFinishedRows();
    void setProjectedPosition(Block& block) const;
    void hardDrop(Block& block);
    void handleScore(int finishedRows);
    bool isTSpin();

    inline const Block& getBlock() const { return *m_currentBlock; }
    inline const Block& getNextBlock() const { return *m_nextBlock; }
    inline const Grid& getGrid() const { return m_grid; }
    inline const GameData& getGameData() const { return m_gameData; }


    Game() { getNewBlock(); }


private:
    Grid m_grid;
    std::unique_ptr<Block> m_currentBlock;
    std::unique_ptr<Block> m_nextBlock;
    bool m_isGameOver = false;
    GameData m_gameData;
};