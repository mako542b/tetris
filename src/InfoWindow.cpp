#include <GameUtils.hpp>
#include <raylib.h>
#include "InfoWindow.hpp"
#include <string>

void InfoWindow::drawNextBlock(Block& block)
{
    auto positions = block.getCurrentAbsPositions();

    for (auto pos : positions)
    {
        Utils::drawInfoTile(pos.posX, pos.posY, getBlockColor(block.m_blockID));
    }
}

void InfoWindow::drawScore()
{
    DrawText(std::to_string(m_score).c_str(), Utils::Config::gameGridSizeX + 50, Utils::Config::paddingYTop + 300, 20, RED);
}

void InfoWindow::handleLevel(int finishedRows)
{
    constexpr int rowsPerLevel = 10;
    static int rowsINLevel = 0;

    rowsINLevel += finishedRows;

    if (rowsINLevel >= rowsPerLevel)
    {
        rowsINLevel = 0;
        m_level++;
    }

}

void InfoWindow::handleScore(ScoreInfo_t info)
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

}
