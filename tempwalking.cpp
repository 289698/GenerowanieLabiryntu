#include "tempwalking.h"

TempWalking::TempWalking(int **mazeTab, int mazeHeight, int mazeWidth, int startingRow, int endingRow)
{
    QueryPerformanceFrequency (&uFreq);
    QueryPerformanceCounter (&uTicks);
    cout << fixed;
    a = uTicks.QuadPart;
    b = uFreq.QuadPart;

    posRow = startingRow;
    posCol = 0;

    printIntTab(mazeTab, startingRow, 0, mazeHeight, mazeWidth, 1);

    while (1)
    {
        char znak;
        znak = getch();

        if((znak == 'w' || znak == 'W') && posRow > 0 && !((mazeTab[posRow][posCol] & 1) == 1))
        {
            posRow--;
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth, 1);
        }
        else if((znak == 'd' || znak == 'D') && posCol < mazeWidth-1 && !((mazeTab[posRow][posCol] & 2) == 2))
        {
            posCol++;
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth, 1);
        }
        else if((znak == 's' || znak == 'S') && posRow < mazeHeight-1 && !((mazeTab[posRow][posCol] & 4) == 4))
        {
            posRow++;
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth, 1);
        }
        else if((znak == 'a' || znak == 'A') && posCol > 0 && !((mazeTab[posRow][posCol] & 8) == 8))
        {
            posCol--;
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth, 1);
        }

        if(znak == 'P' || znak == 'p')
        {
            posRow = endingRow;
            posCol = mazeWidth - 1;
            break;
        }

        if (posRow == endingRow && posCol == mazeWidth-1)
            break;

        if(kbhit())
        {
            cin.clear();
            cin.sync();
        }
    }

    QueryPerformanceCounter (&uTicks);
    a = uTicks.QuadPart - a;

    printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth, 1);
    cout << "\nWygrana!\nCzas przechodzenia: " << a/b << endl;
}
