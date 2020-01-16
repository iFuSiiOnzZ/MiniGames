#pragma once


#ifdef _WIN32
#   define EXPORT extern "C" __declspec(dllexport)
#else
#   define EXPORT extern "C" __attribute__((visibility("default")))
#endif

namespace minigames
{
    typedef struct platform_t
    {
        void(*ClearScreen)(void);
        void(*FlushStdIn)(void);

        bool(*WasKeyDown)(int key);
        bool(*IsKeyDown)(int key);

        void(*WaitFor)(double milliseconds);
    } platform_t;
}
