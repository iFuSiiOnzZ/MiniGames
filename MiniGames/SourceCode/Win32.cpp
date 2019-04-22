/*
    Project includes
*/
#include "headers/internal/Win32.h"

/*
    Lib includes
*/

/*
    C/C++ includes
*/
#include <stdio.h>

/*
    Platfrom includes
*/
#include <Windows.h>

/*
    Defines/Constants
*/

/*
    Enums/Strucsts
*/

///////////////////////////////////////////////////////////////////////////////

void platform::ClearScreen()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    COORD                      homeCoords = { 0, 0 };

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    DWORD cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    if (!FillConsoleOutputCharacterA(
        hStdOut,
        ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void platform::FlushInputBuffer()
{
    int row = 0;
    while ((row = getchar()) != '\n' && row != EOF);
}
