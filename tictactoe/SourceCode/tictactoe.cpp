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

static void fnc_fill_board(const char *boardFormat, const char userInputMatrix[3][3], char *outputData, size_t outputLength)
{
    for (size_t i = 0; i < outputLength; ++i)
    {
        outputData[i] = '\0';
    }

    int row = 0, col = 0;

    while (*boardFormat)
    {
        if (col == 3)
        {
            ++row;
            col = 0;
        }

        if (*boardFormat == 'V') *outputData = userInputMatrix[row][col++];
        else *outputData = *boardFormat;

        ++outputData;
        ++boardFormat;

        if (--outputLength == 0)
        {
            break;
        }
    }
}

static bool fnc_check_win(const char board[3][3], char &winner)
{
    if (board[0][0] != ' ' && board[0][0] == board[0][1] && board[0][1] == board[0][2]) { winner = board[0][0]; return true; }
    if (board[1][0] != ' ' && board[1][0] == board[1][1] && board[1][1] == board[1][2]) { winner = board[1][0]; return true; }
    if (board[2][0] != ' ' && board[2][0] == board[2][1] && board[2][1] == board[2][2]) { winner = board[2][0]; return true; }

    if (board[0][0] != ' ' && board[0][0] == board[1][0] && board[1][0] == board[2][0]) { winner = board[0][0]; return true; }
    if (board[0][1] != ' ' && board[0][1] == board[1][1] && board[1][1] == board[2][1]) { winner = board[0][1]; return true; }
    if (board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2]) { winner = board[0][2]; return true; }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) { winner = board[0][0]; return true; }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) { winner = board[0][2]; return true; }

    winner = ' ';
    return false;
}

static bool fnc_is_board_full(const char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////

extern "C" __declspec(dllexport) const char *GameName(void)
{
    return "Tic Tac Toe";
}

extern "C" __declspec(dllexport) void StarGame(minigames::platform_t *platform)
{
    const char boardFormat[] =
        "     |  1  |  2  |  3  \n"
        "-----+-----+-----+-----\n"
        "  1  |  V  |  V  |  V  \n"
        "-----+-----+-----+-----\n"
        "  2  |  V  |  V  |  V  \n"
        "-----+-----+-----+-----\n"
        "  3  |  V  |  V  |  V  \n";

    char matrix[3][3] =
    {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    };

    platform->FlushStdIn();
    platform->ClearScreen();
    constexpr size_t boarBufferSize = sizeof(boardFormat) + 1;

    char boardBuffer[boarBufferSize] = { 0 };
    int row = 0, col = 0;

    char playerChars[2] = { 'O', 'X' };
    int whichCar = 0; char winner = ' ';

    while (true)
    {
        fnc_fill_board(boardFormat, matrix, boardBuffer, boarBufferSize);
        printf("%s", boardBuffer);

        printf("Select row and cold [player %c] (row,col): ", playerChars[whichCar]);
        scanf_s("%d,%d", &row, &col);

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
        {
            if (matrix[row - 1][col - 1] == ' ')
            {
                matrix[row - 1][col - 1] = playerChars[whichCar];
                whichCar = (whichCar + 1) % sizeof(playerChars);
            }
        }

        if (fnc_check_win(matrix, winner) || fnc_is_board_full(matrix))
        {
            break;
        }

        platform->ClearScreen();
        platform->FlushStdIn();
    }

    if (winner != ' ')
    {
        printf("\r The winnner is: %c!", winner);
    }
    else
    {
        printf("No winner : (");
    }

    platform->FlushStdIn();
    getchar();
}
