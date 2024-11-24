#pragma once

#include "Block.hpp"
#include "raylib.h"

typedef struct ScoreInfo
{
    int clearedRows;
    int hardDroppedRows;
    bool isTSpin;
    bool isGridCleared;
} ScoreInfo_t;

class GameData
{

public:
    void handleLevel(int finishedRows);
    void handleScore(ScoreInfo_t info);
    int getBlockRowPixelOffset() const;

    inline void addScore(int scoreToAdd) { m_score += scoreToAdd; }
    inline int getScore() const { return m_score; }
    inline int getLevel() const { return m_level; }
    inline float getGravityInterval() const { return m_level < 10 ? 1.0f - 0.1f * (m_level - 1) : 0.1f; }
    inline float getNextGravityMove() { return m_nextGravityMove; }
    inline void resetNextGravityMove() { m_nextGravityMove = getGravityInterval(); }
    inline void updateNextGravityMove() { m_nextGravityMove -= GetFrameTime(); }

private:
    int m_score = 0;
    int m_level = 1;
    float m_nextGravityMove;
};