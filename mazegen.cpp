#include "mazegen.h"

MazeGen::MazeGen()
{
    reserveBoolMemory(horizontalBordersTab, 2*mazeHeight, mazeWidth);
    reserveBoolMemory(verticalBordersTab, mazeHeight, 2*mazeWidth);
    reserveBoolMemory(visitedTab, mazeHeight, mazeWidth);
    temp();
    makeBorders();

    cout << "MazeGen Object created!\n";
}
MazeGen::~MazeGen()
{
    clearBoolMemory(horizontalBordersTab, 2*mazeHeight);
    clearBoolMemory(verticalBordersTab, mazeHeight);
    clearBoolMemory(visitedTab, mazeHeight);

    cout << "\n\nMazeGen Object destroyed!\n";
}
void MazeGen::makeBorders()
{
    for (int i=0; i<mazeWidth; i++)
    {
        horizontalBordersTab[0][i] = 1;
        horizontalBordersTab[mazeHeight*2-1][i] = 1;
    }
    for (int i=0; i<mazeHeight; i++)
    {
        verticalBordersTab[i][0] = 1;
        verticalBordersTab[i][mazeWidth*2-1] = 1;
    }
}
void MazeGen::temp()
{
    for (int i=0; i<mazeHeight*2; i++)
        for (int j=0; j<mazeWidth; j++)
            horizontalBordersTab[i][j] = 0;
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth*2; j++)
            verticalBordersTab[i][j] = 0;
}
void MazeGen::optimizeTab()
{
    for (int i=0; i<mazeHeight; i++)
    {
        for (int j=0; j<mazeWidth; j++)
        {
            mazeTab[i][j] =                               0
                    + int(horizontalBordersTab[i*2][j])  *1
                    + int(horizontalBordersTab[i*2+1][j])*2
                    + int(verticalBordersTab[i][j*2])    *4
                    + int(verticalBordersTab[i][j*2+1])  *8;
        }
    }
}

bool** MazeGen::cos(bool a)
{
    cout << "mleko" << endl;
    if(a)
        return horizontalBordersTab;
    return verticalBordersTab;
}

void MazeGen::temp69()
{
    cout << "\n\nMazeGen Object is being prepared!\n\n\n";
    optimizeTab();
    cout << "\n\nMazeGen Object is being printed!\n\n\n";
    printIntTab(mazeTab, mazeHeight, mazeWidth);
}
