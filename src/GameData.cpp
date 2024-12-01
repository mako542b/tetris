#include <GameUtils.hpp>
#include <raylib.h>
#include "GameData.hpp"
#include <string>

void GameData::handleLevel(int finishedRows)
{
    constexpr int rowsPerLevel = 10;
    static int rowsInLevel = 0;

    rowsInLevel += finishedRows;

    if (rowsInLevel >= rowsPerLevel)
    {
        rowsInLevel = 0;
        m_level++;
    }

}

void GameData::handleScore(ScoreInfo_t info)
{
    constexpr int pointsPerRows[] = {0, 100, 250, 450, 700};
    static int comboCount = 0;
    
    addScore(info.hardDroppedRows * 1);

    if (!info.clearedRows)
    {
        comboCount = 0;
        return;
    }

    addScore(pointsPerRows[info.clearedRows] * getLevel());
    addScore(comboCount * 50);

    if (info.isTSpin && info.clearedRows == 2)
        addScore(200);

    if (info.isGridCleared)
        addScore(500);

    comboCount++;
    handleLevel(info.clearedRows);

}

int GameData::getBlockRowPixelOffset() const
{
    float interval = getGravityInterval();
    return static_cast<int>(((interval - m_nextGravityMove) / interval) * Config::tileSizeY);
}
