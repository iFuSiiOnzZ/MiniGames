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
    Enums/Strucsts
*/

///////////////////////////////////////////////////////////////////////////////

extern "C" __declspec(dllexport) const char *GameName(void)
{
    return "Snake";
}

extern "C" __declspec(dllexport) void StarGame(minigames::platform_t *platform)
{

}
