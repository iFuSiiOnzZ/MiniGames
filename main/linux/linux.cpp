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

double fnc_get_current_time_ms()
{
    struct timeval tv = { 0 };
    gettimeofday(&tv, NULL);

    double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
    return time_in_mill;
}

///////////////////////////////////////////////////////////////////////////////

void platform::ClearScreen()
{
    system("clear");
}

void platform::FlushStdIn()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool platform::IsKeyDown(int key)
{
    return false;
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
