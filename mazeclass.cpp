#include "mazeclass.h"

MazeClass::MazeClass()
{
    cout << "Wpisz poczatkowe dane (wysososc, szerokosc)\n\n";

    mazeHeight = getIntValue();
    mazeWidth = getIntValue();

    startingRow = rand() % mazeHeight;
    endingRow = rand() % mazeHeight;

    reserveIntMemory(mazeTab, mazeHeight, mazeWidth);

    generating = new MazeGen(mazeTab, mazeHeight, mazeWidth);

    generating->generateMaze(startingRow, endingRow);

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

