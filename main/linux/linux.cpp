/*
    Project includes
*/
#include "linux.h"

/*
    Lib includes
*/
#include <platform.h>

/*
    C/C++ includes
*/
#include <sys/time.h>
#include <xmmintrin.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

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

static double fnc_get_current_time_ms()
{
    struct timeval tv = { 0 };
    gettimeofday(&tv, NULL);

    double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    return time_in_mill;
}

static int fnc_getPressedKey()
{
    struct termios oldt = { 0 };
    struct termios newt = { 0 };

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}

///////////////////////////////////////////////////////////////////////////////

void platform::ClearScreen()
{
    printf("\033[2J");
    printf("\033[1;1H");
}

void platform::FlushStdIn()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool platform::IsKeyDown(int key)
{
    return fnc_getPressedKey() == key;
}

bool platform::WasKeyDown(int key)
{
    return false;
}

void platform::WaitFor(double milliseconds)
{
    double endTime = fnc_get_current_time_ms() + milliseconds;

    while(true)
    {
        _mm_pause();

        if(fnc_get_current_time_ms() >= endTime)
        {
            break;
        }
    }
}
