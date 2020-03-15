
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

static std::vector<std::string> fnc_get_all_dll(const std::string &path)
{
    std::vector<std::string> names;
    std::string search_path(path + "*.dll");

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

static std::string fnc_getExecutionPath(const std::string &exePath)
{
    return exePath.substr(0, exePath.find_last_of('\\') + 1);
}

int main(int argc, char *argv[])
{
    std::string exePath(fnc_getExecutionPath(argv[0]));
    std::vector<std::shared_ptr<Game>> games(fnc_load_game(fnc_get_all_dll(exePath)));

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

        if (platform::IsKeyDown(VK_UP))
        {
            if (userMenuOption == 0) userMenuOption = (int)games.size();
            else --userMenuOption;
        }

        if (platform::IsKeyDown(VK_DOWN))
        {
            if (userMenuOption == games.size()) userMenuOption = 0;
            else ++userMenuOption;
        }

        if (platform::IsKeyDown(VK_RETURN))
        {
            if (userMenuOption != 0) games[userMenuOption - 1]->startGame(&platformFunctions);
            else break;
        }

        platform::WaitFor(50);
    }

    return 0;
}
