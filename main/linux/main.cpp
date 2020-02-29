/*
    Project includes
*/
#include "DLLHelper.h"
#include "linux.h"

/*
    Lib includes
*/
#include <platform.h>

/*
    C/C++ includes
*/
#include <stdio.h>
#include <stdlib.h>

/*
    Platfrom includes
*/

/*
    Defines/Constants
*/
typedef const char *(*GameName)(void);
typedef void(*StartGame)(minigames::platform_t *);

/*
    Enums/Strucsts
*/

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    DLLHelper DllHelper("./tictactoe.so");
    minigames::platform_t platformFunctions = { 0 };

    platformFunctions.ClearScreen = &platform::ClearScreen;
    platformFunctions.FlushStdIn = &platform::FlushStdIn;

    platformFunctions.WasKeyDown = &platform::WasKeyDown;
    platformFunctions.IsKeyDown = &platform::IsKeyDown;

    platformFunctions.WaitFor = &platform::WaitFor;


    GameName gameName = DllHelper ["GameName"];
    StartGame startGame = DllHelper["StarGame"];

    printf("%s\n", gameName());
    startGame(&platformFunctions);
    return EXIT_SUCCESS;
}
