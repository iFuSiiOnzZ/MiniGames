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
#include <stdlib.h>

/*
    Platfrom includes
*/
#include <dlfcn.h>

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

    void *dllHandle = dlopen("./tictactoe.so", RTLD_NOW);
    if(dllHandle == nullptr)
    {
        printf("%s\n", dlerror());
        return EXIT_SUCCESS;
    }

    GameName gameName = (GameName)dlsym(dllHandle, "GameName");
    StartGame startGame = (StartGame)dlsym(dllHandle, "StarGame");

    printf("%s\n", gameName());

    dlclose(dllHandle);
    return EXIT_SUCCESS;
}
