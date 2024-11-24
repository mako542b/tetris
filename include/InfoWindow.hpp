#pragma once

#include "Block.hpp"

typedef struct ScoreInfo
{
    int clearedRows;
    int hardDroppedRows;
    bool isTSpin;
    bool isGridCleared;
} ScoreInfo_t;

class InfoWindow
{

public:
    void drawNextBlock(Block& block);
    void drawScore();
    void handleLevel(int finishedRows);
    void handleScore(ScoreInfo_t info);

    inline void addScore(int scoreToAdd) { m_score += scoreToAdd; }
    inline int getLevel() { return m_level; }

private:
    int m_score = 0;
    int m_level = 1;
};