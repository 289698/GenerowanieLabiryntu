#include "mazegen.h"

MazeGen::MazeGen()
{
    reserveBordersMemory(bordersTab, mazeHeight, mazeWidth);
    reserveBoolMemory(visitedTab, mazeHeight, mazeWidth);

    temp(1);
    temp2();

    cout << "\nMazeGen Object created!\n";
}
MazeGen::~MazeGen()
{
    clearBordersMemory(bordersTab, mazeHeight, mazeWidth);
    clearBoolMemory(visitedTab, mazeHeight);

    cout << "\nMazeGen Object destroyed!\n";
}
/*
PointXY MazeGen::makeRandomPath(PointXY current)
{
    visitedTab[current.x][current.y] = 1;
    bordersTab[i][j];
    if()
        makeRandomPath();
}

bool MazeGen::findNextPoint(PointXY &current)
{
    do
    {
        int direction;                //    1
        srand(time(0));               //  4 O 2
        direction = 1 + rand() % 4;   //    3
    }
    while();
}

bool MazeGen::randomBool()
{
    srand(time(0));
    //bool a;
    //a = rand() % 2;
    return rand() % 2;
}
*/
void MazeGen::temp2()
{
    cout << "\nMazeGen Object is being prepared!\n";
    rewriteTab();
    cout << "\nMazeGen Object is being printed!\n";
    printIntTab(mazeTab, mazeHeight, mazeWidth);
}

void MazeGen::rewriteTab()
{
    for (int i=0; i<mazeHeight; i++)
    {
        for (int j=0; j<mazeWidth; j++)
        {
            mazeTab[i][j] = 0
                    + int(*(bordersTab[i][j].N)) *1
                    + int(*(bordersTab[i][j].E)) *2
                    + int(*(bordersTab[i][j].S)) *4
                    + int(*(bordersTab[i][j].W)) *8;
        }
        cout << endl;
    }

    cout << "\nTablica zoptymalizowana\n";
}

void MazeGen::temp(int a)
{
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
        {
            *(bordersTab[i][j].N) = a;
            *(bordersTab[i][j].E) = a;
            *(bordersTab[i][j].S) = a;
            *(bordersTab[i][j].W) = a;
        }
    /*
    for (int i=0; i<mazeHeight; i++)
    {
        *(bordersTab[i][0].W) = 1;
        *(bordersTab[i][mazeWidth-1].E) = 1;
    }
    for (int j=0; j<mazeWidth; j++)
    {
        *(bordersTab[0][j].N) = 1;
        *(bordersTab[mazeHeight-1][j].S) = 1;
    }
*/

    cout << "\nTablica wyzerowana\n";
}

void MazeGen::reserveBordersMemory (Borders **&adress, int w, int k)
{
    adress = new Borders *[w];
    for (int i=0; i<w; i++)
        adress[i] = new Borders [k];
    for (int i=0; i<w; i++)
        for (int j=0; j<k; j++)
        {
            adress[i][j].N = new bool;
            adress[i][j].E = new bool;
            adress[i][j].S = new bool;
            adress[i][j].W = new bool;
        }

    for (int i=1; i<w; i++)
        for(int j=1; j<k; j++)
        {
            bordersTab[i][j].N = bordersTab[i-1][j].S;
            bordersTab[i][j].W = bordersTab[i][j-1].E;
        }
    for (int i=1; i<w; i++)
        bordersTab[i][0].N = bordersTab[i-1][0].S;
    for (int j=1; j<k; j++)
        bordersTab[0][j].W = bordersTab[0][j-1].E;

    cout << "\nZadeklarowano pamiec na tablice typu Borders\n";
}

void MazeGen::clearBordersMemory (Borders **&adress, int w, int k)
{
    for (int i=0; i<w; i++)
        for (int j=0; j<k; j++)
        {
            delete adress[i][j].E;
            delete adress[i][j].S;
        }
    for (int i=0; i<w; i++)
        delete adress[i][0].W;
    for (int j=0; j<k; j++)
        delete adress[0][j].N;

    for (int i=0; i<w; i++)
        delete[] adress[i];
    delete[] adress;

    cout << "\nUsunieto pamiec na tablice typu Borders\n";
}
