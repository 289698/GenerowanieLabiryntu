#include "mazeclass.h"

MazeClass::MazeClass()
{
    cout << "Wpisz poczatkowe dane (wysososc, szerokosc)\n\n";

    mazeHeight = getIntValue();
    mazeWidth = getIntValue();

    reserveIntMemory(mazeTab, mazeHeight, mazeWidth);

    generating = new MazeGen(mazeTab, mazeHeight, mazeWidth);

    generating->generateMaze();

    printIntTab(mazeTab, mazeHeight, mazeWidth);

    delete generating;
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

