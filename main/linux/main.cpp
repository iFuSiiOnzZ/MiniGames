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

#include <string.h>
#include <dirent.h>

#include <string>
#include <vector>
#include <memory>

/*
    Platfrom includes
*/

/*
    Defines/Constants
*/
typedef const char *(*GameName)(void);
typedef void(*StartGame)(minigames::platform_t *);

static const int KEY_DOWN = 66;
static const int KEY_UP = 65;
static const int KEY_RIGHT = 67;
static const int KEY_LEFT = 68;

/*
    Enums/Structs
*/

///////////////////////////////////////////////////////////////////////////////

class Game
{
private:
    DLLHelper dllHelper;

public:
    StartGame startGame;
    GameName gameName;

public:
    explicit Game(const std::string &dllName) : dllHelper(dllName.c_str())
    {
        startGame = dllHelper["StarGame"];
        gameName = dllHelper["GameName"];
    }

    bool isValidGame()
    {
        return startGame != nullptr && gameName != nullptr;
    }
};

///////////////////////////////////////////////////////////////////////////////

static std::vector<std::string> fnc_get_all_dll(const char *path)
{
    std::vector<std::string> names;
    DIR* dirFile = opendir(path);

    if (!dirFile)
    {
        return names;
    }

    struct dirent *hFile = NULL;
    while ((hFile = readdir(dirFile)) != NULL )
    {
        if (strstr( hFile->d_name, ".so" ))
        {
            names.emplace_back(path);
            names.back().append(hFile->d_name);
        }
    }

    closedir( dirFile );
    return names;
}

static std::vector<std::shared_ptr<Game>> fnc_load_game(const std::vector<std::string> &gameDlls)
{
    std::vector<std::shared_ptr<Game>> games;

    for (auto dll : gameDlls)
    {
        std::shared_ptr<Game> game = std::make_shared<Game>(dll);
        if (game->isValidGame()) games.emplace_back(game);
    }

    return games;
}

int main(int argc, char *argv[])
{
    std::vector<std::shared_ptr<Game>> games(fnc_load_game(fnc_get_all_dll("./")));
    minigames::platform_t platformFunctions = { 0 };
    size_t userMenuOption = 0;

    platformFunctions.ClearScreen = &platform::ClearScreen;
    platformFunctions.FlushStdIn = &platform::FlushStdIn;

    platformFunctions.WasKeyDown = &platform::WasKeyDown;
    platformFunctions.IsKeyDown = &platform::IsKeyDown;

    platformFunctions.WaitFor = &platform::WaitFor;

    while (true)
    {
        platform::FlushStdIn();
        platform::ClearScreen();
        platform::updateInput();

        printf("\n");
        printf("    ********************************************************************************\n");
        printf("    *                                  Mini Games                                  *\n");
        printf("    ********************************************************************************\n");

        char c = (userMenuOption == 0) ? '>' : ' ';
        printf("      %c Exit\n", c);

        for (size_t i = 1; i < games.size() + 1; ++i)
        {
            char c = (i == userMenuOption) ? '>' : ' ';
            printf("      %c Play [%s]\n", c, games[i - 1]->gameName());
        }

        if(platform::IsKeyDown(KEY_UP))
        {
            if(userMenuOption == 0) userMenuOption = (int)games.size();
            else --userMenuOption;
        }

        if(platform::IsKeyDown(KEY_DOWN))
        {
            if(userMenuOption == games.size()) userMenuOption = 0;
            else ++userMenuOption;
        }

        if(platform::IsKeyDown(10))
        {
            if(userMenuOption != 0) games[userMenuOption - 1]->startGame(&platformFunctions);
            else break;
        }

        platform::WaitFor(10);
    }

    platform::ClearScreen();
    return EXIT_SUCCESS;
}
