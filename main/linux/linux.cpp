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
#include <sys/ioctl.h>
#include <xmmintrin.h>

#include <termios.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Platfrom includes
*/

/*
    Defines/Constants
*/

/*
    Enums/Structs
*/

/*
    Static variables
*/

static int gCurrentKeyDown[256] = { 0 };
static int gLastKeyDown[256] = { 0 };

///////////////////////////////////////////////////////////////////////////////

static double fnc_get_current_time_ms()
{
    struct timeval tv = { 0 };
    gettimeofday(&tv, NULL);

    double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    return time_in_mill;
}

static int fnc_kbhit()
{
    struct termios term = { 0 };
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int byteswaiting = 0;
    ioctl(STDIN_FILENO, FIONREAD, &byteswaiting);

    term.c_lflag |= (ICANON | ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    return byteswaiting;
}

///////////////////////////////////////////////////////////////////////////////

void platform::ClearScreen()
{
    printf("\033[2J");
    printf("\033[1;1H");
}

void platform::FlushStdIn()
{
}

void platform::updateInput()
{
    memcpy(gLastKeyDown, gCurrentKeyDown, sizeof(gLastKeyDown));
    memset(gCurrentKeyDown, 0, sizeof(gCurrentKeyDown));

    for(int numChars = fnc_kbhit(); numChars > 0; --numChars)
    {
        int ch = getchar();
        gCurrentKeyDown[ch] = 1;
    }
}

bool platform::IsKeyDown(int key)
{
    return gCurrentKeyDown[key];
}

bool platform::WasKeyDown(int key)
{
    return gCurrentKeyDown[key] != 1 && gLastKeyDown[key] == 0;
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
