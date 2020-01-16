/*
    Project includes
*/
#include "Win32.h"

/*
    Lib includes
*/

/*
    C/C++ includes
*/
#include <stdio.h>
#include <conio.h>

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

void platform::FlushStdIn()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool platform::IsKeyDown(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) == 0x8000;
}

bool platform::WasKeyDown(int key)
{
    return (GetAsyncKeyState(key) & 0x0001) == 0x0001;
}

void platform::WaitFor(double milliseconds)
{
    LARGE_INTEGER Frequency = { 0 };
    QueryPerformanceFrequency(&Frequency);

    LARGE_INTEGER startTime = { 0 };
    QueryPerformanceCounter(&startTime);

    while (true)
    {
        _mm_pause();

        LARGE_INTEGER currentTime = { 0 };
        QueryPerformanceCounter(&currentTime);

        LONGLONG llTimeDiff = currentTime.QuadPart - startTime.QuadPart;
        double dftDuration = (double)llTimeDiff * 1000.0 / (double)Frequency.QuadPart;

        if (dftDuration >= milliseconds)
        {
            break;
        }
    }
}

