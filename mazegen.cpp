#include "mazegen.h"

MazeGen::MazeGen()
{
    QueryPerformanceCounter (&uTicks);
    QueryPerformanceFrequency (&uFreq);

    ticks = uTicks.QuadPart;
    freq = uFreq.QuadPart;
    cout << fixed;

    reserveBordersMemory();
    reserveBoolMemory(visitedTab, mazeHeight, mazeWidth);

    temp(1); // jedynkuje krawedzie
    temp3(); // zeruje visitedTab

    generateMaze();

    QueryPerformanceCounter (&uTicks);
    ticks = uTicks.QuadPart - ticks;
    cout << "\nCzas przygotowania obiektu: " << ticks / freq << endl;

    //temp2(1, 0); // drukuje tablice
}

MazeGen::~MazeGen()
{
    clearBordersMemory();
    clearBoolMemory(visitedTab, mazeHeight);
}

void MazeGen::generateMaze()
{
    PointXY currentPos;
    currentPos.row = getIntValue();
    currentPos.col = getIntValue();
    int counter = 0;

    bool a = 0;
    makeStartingPath(currentPos, counter, a);

    while (a)
    {
        temp(1);
        temp3();
        makeStartingPath(currentPos, counter, a);
    }
    temp2(1, 0);
    cout << endl << counter << endl;
    Sleep (1000);
    while (findNextPoint(currentPos))
        makeRandomPath(currentPos);
    temp2(0, 0);
}

void MazeGen::makeStartingPath(PointXY currentPos, int &counter, bool &a)
{
    visitedTab[currentPos.row][currentPos.col] = 1;
    char direction;
    direction = randomDirection(currentPos);

    if (direction == 'X')
    {
        a = 1;
        return;
    }

    if (currentPos.col == mazeWidth-1)
    {
        a = 0;
        return;
    }

    //------------
    if (direction == 'N')
    {
        *(bordersTab[currentPos.row][currentPos.col].N) = 0;
        currentPos.row--;
    }
    if (direction == 'E')
    {
        *(bordersTab[currentPos.row][currentPos.col].E) = 0;
        currentPos.col++;
    }
    if (direction == 'S')
    {
        *(bordersTab[currentPos.row][currentPos.col].S) = 0;
        currentPos.row++;
    }
    if (direction == 'W')
    {
        *(bordersTab[currentPos.row][currentPos.col].W) = 0;
        currentPos.col--;
    }
    counter++;
    makeStartingPath(currentPos, counter, a);
    return;
}

void MazeGen::makeRandomPath(PointXY currentPos)
{
    visitedTab[currentPos.row][currentPos.col] = 1;
    char direction;
    direction = randomDirection(currentPos);

    if (direction == 'X')
        return;
    if (direction == 'N')
    {
        *(bordersTab[currentPos.row][currentPos.col].N) = 0;
        currentPos.row--;
    }
    if (direction == 'E')
    {
        *(bordersTab[currentPos.row][currentPos.col].E) = 0;
        currentPos.col++;
    }
    if (direction == 'S')
    {
        *(bordersTab[currentPos.row][currentPos.col].S) = 0;
        currentPos.row++;
    }
    if (direction == 'W')
    {
        *(bordersTab[currentPos.row][currentPos.col].W) = 0;
        currentPos.col--;
    }

    makeRandomPath(currentPos);
    return;
}

char MazeGen::randomDirection(PointXY currentPos)
{
    bool dirN = 0,
         dirE = 0,
         dirS = 0,
         dirW = 0;
    int numberOfDirections = 0,
        i = 0;
    char *tab,
         direction;

    if (currentPos.row-1 >= 0            && !(visitedTab[currentPos.row-1][currentPos.col])) {
        dirN = 1; numberOfDirections++;
    }
    if (currentPos.col+1 <= mazeWidth-1  && !(visitedTab[currentPos.row][currentPos.col+1])) {
        dirE = 1; numberOfDirections++;
    }
    if (currentPos.row+1 <= mazeHeight-1 && !(visitedTab[currentPos.row+1][currentPos.col])) {
        dirS = 1; numberOfDirections++;
    }
    if (currentPos.col-1 >= 0            && !(visitedTab[currentPos.row][currentPos.col-1])) {
        dirW = 1; numberOfDirections++;
    }

    tab = new char[numberOfDirections];

    if (dirN) {
        tab[i] = 'N'; i++;
    }
    if (dirE) {
        tab[i] = 'E'; i++;
    }
    if (dirS) {
        tab[i] = 'S'; i++;
    }
    if (dirW) {
        tab[i] = 'W'; i++;
    }

    if (numberOfDirections == 0)
        return 'X';

    i = rand() % numberOfDirections;

    direction = tab[i];

    delete[] tab;

    return direction;
}

bool MazeGen::findNextPoint(PointXY &currentPos)
{
    for (int i=0; i<mazeHeight; i++)
    {
        for (int j=0; j<mazeWidth; j++) if (!visitedTab[i][j])
        {
            bool isPointFound = 0;

                 if (j < mazeWidth-1  && visitedTab[i][j+1])
            {
                *(bordersTab[i][j].E) = 0;
                isPointFound = 1;
            }
            else if (i < mazeHeight-1 && visitedTab[i+1][j])
            {
                *(bordersTab[i][j].S) = 0;
                isPointFound = 1;
            }
            else if (j > 0            && visitedTab[i][j-1])
            {
                *(bordersTab[i][j].W) = 0;
                isPointFound = 1;
            }
            else if (i > 0            && visitedTab[i-1][j])
            {
                *(bordersTab[i][j].N) = 0;
                isPointFound = 1;
            }

            if (isPointFound)
            {
                currentPos.row = i;
                currentPos.col = j;
                return 1;
            }
        }
    }
    return 0;
}

void MazeGen::temp3()
{
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
            visitedTab[i][j] = 0;
}

void MazeGen::temp2(bool clean, int sleepTime)
{
    //cout << "\nMazeGen Object is being prepared!\n";
    rewriteTab();
    //cout << "\nMazeGen Object is being printed!\n";
    if (clean)
        system("cls");
    printIntTab(mazeTab, visitedTab, mazeHeight, mazeWidth);
    Sleep(sleepTime);
}

void MazeGen::rewriteTab()
{
    for (int i=0; i<mazeHeight; i++)
    {
        for (int j=0; j<mazeWidth; j++)
        {
            mazeTab[i][j] = 0
                    + int(*(bordersTab[i][j].N)) * 1
                    + int(*(bordersTab[i][j].E)) * 2
                    + int(*(bordersTab[i][j].S)) * 4
                    + int(*(bordersTab[i][j].W)) * 8;
        }
    }
}

void MazeGen::temp(bool a)
{
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
        {
            *(bordersTab[i][j].N) = a;
            *(bordersTab[i][j].E) = a;
            *(bordersTab[i][j].S) = a;
            *(bordersTab[i][j].W) = a;
        }
}

void MazeGen::reserveBordersMemory ()
{
    bordersTab = new Borders *[mazeHeight];

    for (int i=0; i<mazeHeight; i++)
        bordersTab[i] = new Borders [mazeWidth];

    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
        {
            bordersTab[i][j].N = new bool;
            bordersTab[i][j].E = new bool;
            bordersTab[i][j].S = new bool;
            bordersTab[i][j].W = new bool;
        }

    for (int i=1; i<mazeHeight; i++)
        for(int j=1; j<mazeWidth; j++)
        {
            bordersTab[i][j].N = bordersTab[i-1][j].S;
            bordersTab[i][j].W = bordersTab[i][j-1].E;
        }

    for (int i=1; i<mazeHeight; i++)
        bordersTab[i][0].N = bordersTab[i-1][0].S;

    for (int j=1; j<mazeWidth; j++)
        bordersTab[0][j].W = bordersTab[0][j-1].E;
}

void MazeGen::clearBordersMemory ()
{
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
        {
            delete bordersTab[i][j].E;
            delete bordersTab[i][j].S;
        }

    for (int i=0; i<mazeHeight; i++)
        delete bordersTab[i][0].W;

    for (int j=0; j<mazeWidth; j++)
        delete bordersTab[0][j].N;

    for (int i=0; i<mazeHeight; i++)
        delete[] bordersTab[i];
    delete[] bordersTab;
}
