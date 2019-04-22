#pragma once

namespace minigames
{
    typedef struct platform_t
    {
        void(*ClearScreen)(void);
        void(*FlushStdIn)(void);
    } platform_t;
}
