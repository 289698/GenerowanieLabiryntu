#include "mazeclass.h"

MazeClass::MazeClass()
{
    cout << "\nWpisz pocz dane\n";

    mazeHeight = getIntValue();
    mazeWidth = getIntValue();
    startingRow = getIntValue();

    reserveIntMemory(mazeTab, mazeHeight, mazeWidth);

    generating = new MazeGen(mazeTab, mazeHeight, mazeWidth);

    endingRow = generating->generateMaze(startingRow);

    printIntTab(mazeTab, startingRow, 0, mazeHeight, mazeWidth);

    delete generating;

    walking = new TempWalking(mazeTab, mazeHeight, mazeWidth, startingRow, endingRow);
}

MazeClass::~MazeClass()
{

    clearIntMemory(mazeTab, mazeHeight);
}

int MazeClass::getIntValue()
{
    int a;
    cin >> a;
    return a;
}

void MazeClass::reserveIntMemory (int **&adress, int w, int k)
{
    adress = new int *[w];
    for (int i=0; i<w; i++)
        adress[i] = new int [k];
}

void MazeClass::clearIntMemory (int **&adress, int w)
{
    for (int i=0; i<w; i++)
        delete[] adress[i];
    delete adress;
}

