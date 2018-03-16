#include "mazeclass.h"

MazeClass::MazeClass()
{
    cout << "\nWpisz pocz dane\n";

    mazeHeight = getIntValue();
    mazeWidth = getIntValue();
    reserveIntMemory(mazeTab, mazeHeight, mazeWidth);

    cout << "\nMazeClass Object created!\n";
}

MazeClass::~MazeClass()
{
    clearIntMemory(mazeTab, mazeHeight);

    cout << "\nMazeClass Object destroyed!\n";
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

void MazeClass::reserveBoolMemory (bool **&adress, int w, int k)
{
    adress = new bool *[w];
    for (int i=0; i<w; i++)
        adress[i] = new bool [k];
}

void MazeClass::clearBoolMemory (bool **&adress, int w)
{
    for (int i=0; i<w; i++)
        delete[] adress[i];
    delete adress;
}
