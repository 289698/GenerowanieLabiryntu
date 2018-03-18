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

    while (1)
    {
        char znak;
        znak = getch();

        if((znak == 'w' || znak == 'W') && posRow > 0 && !((mazeTab[posRow][posCol] & 1) == 1))
        {
            posRow--;
            system("cls");
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth);
        }
        else if((znak == 'd' || znak == 'D') && posCol < mazeWidth-1 && !((mazeTab[posRow][posCol] & 2) == 2))
        {
            posCol++;
            system("cls");
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth);
        }
        else if((znak == 's' || znak == 'S') && posRow < mazeHeight-1 && !((mazeTab[posRow][posCol] & 4) == 4))
        {
            posRow++;
            system("cls");
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth);
        }
        else if((znak == 'a' || znak == 'A') && posCol > 0 && !((mazeTab[posRow][posCol] & 8) == 8))
        {
            posCol--;
            system("cls");
            printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth);
        }
        if(znak == 'P')
            break;

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

    system("cls");
    printIntTab(mazeTab, posRow, posCol, mazeHeight, mazeWidth);
    cout << "\nWygrana!\nCzas przechodzenia: " << a/b << endl;
}
