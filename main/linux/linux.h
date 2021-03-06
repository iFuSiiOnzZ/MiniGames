#pragma once

namespace platform
{
    void ClearScreen();
    void FlushStdIn();

    bool WasKeyDown(int);
    bool IsKeyDown(int);
    void updateInput();

    void WaitFor(double);
}
