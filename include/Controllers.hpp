#pragma once

#include "raylib.h"

class Controllers
{
public:
    static bool inputMoveDown() { return IsKeyDown(KEY_DOWN); }
    static bool inputMoveLeftPressed() { return IsKeyPressed(KEY_LEFT); }
    static bool inputMoveLeftDown() { return IsKeyDown(KEY_LEFT); }
    static bool inputMoveRightPressed() { return IsKeyPressed(KEY_RIGHT); }
    static bool inputMoveRightDown() { return IsKeyDown(KEY_RIGHT); }
    static bool inputHardDrop() { return IsKeyPressed(KEY_SPACE); }
    static bool inputRotateCW() { return IsKeyPressed(KEY_X); }
    static bool inputRotateCCW() { return IsKeyPressed(KEY_Z); }
    static bool inputNewGame() { return IsKeyPressed(KEY_N); }
    static bool inputTogglePause() { return IsKeyPressed(KEY_O) || IsKeyPressed(KEY_ZERO); }
    static bool inputToggleProjection() { return IsKeyPressed(KEY_P); }
};