#include "mazeclass.h"

MazeClass::MazeClass()
{
    cout << "Wpisz poczatkowe dane (zalecane: wysososc <5,40>, szerokosc <10,90>, trudnosc {1,2,3})\n\n";

    mazeHeight = getIntValue();
    mazeWidth = getIntValue();
    int difficulty = getIntValue();

    startingRow = rand() % mazeHeight;

    reserveIntMemory(mazeTab, mazeHeight, mazeWidth);

    generating = new MazeGen(mazeTab, mazeHeight, mazeWidth, difficulty);

    endingRow = generating->generateMaze(startingRow);

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

