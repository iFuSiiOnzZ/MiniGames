
/*
    Project includes
*/
#include "DLLHelper.h"
#include "Win32.h"

/*
    Lib includes
*/
#include <platform.h>

/*
    C/C++ includes
*/
#include <vector>
#include <string>
#include <memory>

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

std::vector<std::string> fnc_get_all_dll(const char *path)
{
    std::vector<std::string> names;
    std::string search_path(std::string(path) + "/*.dll");

    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return names;
    }

    do
    {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            names.push_back(fd.cFileName);
        }
    } while (::FindNextFileA(hFind, &fd));

    ::FindClose(hFind);
    return names;
}

std::vector<std::shared_ptr<Game>> fnc_load_game(const std::vector<std::string> &gameDlls)
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
    int userMenuOption = 0;

    platformFunctions.ClearScreen = &platform::ClearScreen;
    platformFunctions.FlushStdIn = &platform::FlushStdIn;

    platformFunctions.WasKeyDown = &platform::WasKeyDown;
    platformFunctions.IsKeyDown = &platform::IsKeyDown;

    platformFunctions.WaitFor = &platform::WaitFor;

    const char *menuHeader =
        "\n"
        "    ********************************************************************************\n"
        "    *                                  Mini Games                                  *\n"
        "    ********************************************************************************\n";

    while (true)
    {
        printf("%s\n", menuHeader);
        printf("        0 - Exit\n");

        for (size_t i = 0; i < games.size(); ++i)
        {
            printf("        %zd - Play [%s]\n", i + 1, games[i]->gameName());
        }

        printf("\n        Select and option: ");
        scanf_s("%d", &userMenuOption);

        if (userMenuOption == 0)
        {
            break;
        }
        else if (userMenuOption < 0)
        {
            // NOTE(Andrei): Nothing to do, invalid input
        }
        else if (userMenuOption <= games.size())
        {
            games[userMenuOption - (int)1]->startGame(&platformFunctions);
        }

        platform::ClearScreen();
        platform::FlushStdIn();
    }

    return 0;
}
