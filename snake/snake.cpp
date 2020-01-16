/*
    Project includes
*/

/*
    Lib includes
*/
#include <platform.h>

/*
    C/C++ includes
*/
#include <stdio.h>

/*
    Platfrom includes
*/

/*
    Defines/Constants
*/

/*
    Enums/Structs
*/

enum class Direction : int
{
    UP = 38,    // VK_UP
    DOWN = 40,  // VK_DOWN
    LEFT = 37,  // VK_LEFT
    RIGHT = 39  // VK_RIGHT
};

typedef struct Coordinate
{
    int x, y;
    Direction direction;
} Coordinate;

///////////////////////////////////////////////////////////////////////////////

const char* toString(Direction direction)
{
    switch (direction)
    {
        #define _case_(x) case x: return #x
            _case_(Direction::UP);
            _case_(Direction::DOWN);
            _case_(Direction::LEFT);
            _case_(Direction::RIGHT);
        #undef _case_
    }

    return "Undefined Direction";
}

extern "C" __declspec(dllexport) const char *GameName(void)
{
    return "Snake";
}

extern "C" __declspec(dllexport) void StarGame(minigames::platform_t *platform)
{
    static const int ESCAPE = 27;
    Direction currentDirection = Direction::UP;

    while (!platform->WasKeyDown(ESCAPE))
    {
        platform->ClearScreen();

        if (platform->WasKeyDown((int)Direction::UP))
        {
            currentDirection = Direction::UP;
        }
        else if (platform->WasKeyDown((int)Direction::DOWN))
        {
            currentDirection = Direction::DOWN;
        }
        else if (platform->WasKeyDown((int)Direction::LEFT))
        {
            currentDirection = Direction::LEFT;
        }
        else if (platform->WasKeyDown((int)Direction::RIGHT))
        {
            currentDirection = Direction::RIGHT;
        }

        printf("%s", toString(currentDirection));
        platform->WaitFor(500);
    }
}
