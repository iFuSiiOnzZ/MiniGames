#pragma once

namespace minigames
{
    typedef struct platform_t
    {
        void(*ClearScreen)(void);
        void(*FlushStdIn)(void);

        bool(*WasKeyDown)(int key);
        bool(*IsKeyDown)(int key);
    } platform_t;
}
