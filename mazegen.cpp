#include "mazegen.h"

MazeGen::MazeGen()
{

    QueryPerformanceCounter (&uTicks);
    QueryPerformanceFrequency (&uFreq);

    ticks = uTicks.QuadPart;
    freq = uFreq.QuadPart;
    cout << fixed;

    reserveBordersMemory(bordersTab, mazeHeight, mazeWidth);
    reserveBoolMemory(visitedTab, mazeHeight, mazeWidth);

    temp(1); // jedynkuje krawedzie
    temp3(); // zeruje visitedTab
    startingPoint.w = 14; startingPoint.k = 4;

    QueryPerformanceCounter (&uTicks);
    ticks = uTicks.QuadPart - ticks;
    cout << "\nCzas przygotowania obiektu: " << ticks / freq << endl;

    makeRandomPath(startingPoint);
    while(findNextPoint());
    //cin.ignore();

    temp2(); // drukuje tablice

    cout << "\nMazeGen Object created!\n";
}
MazeGen::~MazeGen()
{
    clearBordersMemory(bordersTab, mazeHeight, mazeWidth);
    clearBoolMemory(visitedTab, mazeHeight);

    cout << "\nMazeGen Object destroyed!\n";
}

void MazeGen::makeRandomPath(PointXY currentPos)
{
    //cout << "\nmakeRandomPath\n";
    //cout << "\nIDE\n";
    char dir;
    int a;
    visitedTab[currentPos.w][currentPos.k] = 1;
    if(findNextDir(currentPos, dir, a))
    {
        //cout << "\nNISZCZE SCIANE\n";
        if (dir == 'N')
        {
            *(bordersTab[currentPos.w][currentPos.k].N) = 0;
            currentPos.w--;
        }
        if (dir == 'E')
        {
            *(bordersTab[currentPos.w][currentPos.k].E) = 0;
            currentPos.k++;
        }
        if (dir == 'S')
        {
            *(bordersTab[currentPos.w][currentPos.k].S) = 0;
            currentPos.w++;
        }
        if (dir == 'W')
        {
            *(bordersTab[currentPos.w][currentPos.k].W) = 0;
            currentPos.k--;
        }
        //temp2();
        makeRandomPath(currentPos);
        //cout << a << " "; // usunac wypis a
    }
    return;
}

bool MazeGen::findNextDir(PointXY currentPos, char &dir, int &a)
{
    //cout << "\nfindNextDir\n";
    //cout << "\nSZUKAM\n";
    bool dirN = 0,
         dirE = 0,
         dirS = 0,
         dirW = 0;
    int dirNumber = 0;
    // czy można to uprościć ???
    // sprawdzam dostepne kierunki
    if (currentPos.w-1 >= 0)
        if (!(visitedTab[currentPos.w-1][currentPos.k]))
        {
            dirN = 1;
            dirNumber++;
        }
    if (currentPos.k+1 <= mazeWidth-1)
        if (!(visitedTab[currentPos.w][currentPos.k+1]))
        {
            dirE = 1;
            dirNumber++;
        }
    if (currentPos.w+1 <= mazeHeight-1)
        if (!(visitedTab[currentPos.w+1][currentPos.k]))
        {
            dirS = 1;
            dirNumber++;
        }
    if (currentPos.k-1 >= 0)
        if (!(visitedTab[currentPos.w][currentPos.k-1]))
        {
            dirW = 1;
            dirNumber++;
        }

    if (!dirNumber) // jesli nie mozna sie ruszyc
    {
        //cout << "\nJestes bananem\n";
        return 0;
    }

    char *tab; // tworze tablice z ktorej bede losowac kierunek
    tab = new char[dirNumber];
    int i = 0;

    if (dirN) { tab[i] = 'N'; i++; }
    if (dirE) { tab[i] = 'E'; i++; }
    if (dirS) { tab[i] = 'S'; i++; }
    if (dirW) { tab[i] = 'W'; i++; }
// losuje kierunek
    a = rand();
    i = a % dirNumber;

    //cout << i << " ";

    dir = tab[i];

    delete[] tab;
    return 1;
}

bool MazeGen::findNextPoint()
{
    //cout << "\nfindNextPoint\n";
    //temp2();
    //cin.ignore();
    for (int i=0; i<mazeHeight-1; i++)
    {
        for (int j=0; j<mazeWidth-1; j++)
            if (!visitedTab[i][j])
            {
                //cout << "\n( " << i << " , " << j << " )\n";
                if(visitedTab[i][j+1])
                {
                    *(bordersTab[i][j].E) = 0;
                    PointXY start;
                    start.w = i;
                    start.k = j;
                    makeRandomPath(start);
                    return 1;
                }
                if(visitedTab[i+1][j])
                {
                    *(bordersTab[i][j].S) = 0;
                    PointXY start;
                    start.w = i;
                    start.k = j;
                    makeRandomPath(start);
                    return 1;
                }
            }
    }
    return 0;
}

/*bool MazeGen::randomBool()
{
    srand(time(0));
    //bool a;
    //a = rand() % 2;
    return rand() % 2;
}*/

void MazeGen::temp3()
{
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
            visitedTab[i][j] = 0;
}

void MazeGen::temp2()
{
    //cout << "\nMazeGen Object is being prepared!\n";
    rewriteTab();
    //cout << "\nMazeGen Object is being printed!\n";
    //system("cls");
    printIntTab(mazeTab, visitedTab, mazeHeight, mazeWidth);
    //Sleep(500);
}

void MazeGen::rewriteTab()
{
    cout << "\nkomisk\n";
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

    cout << "\nTablica zoptymalizowana\n";
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

    cout << "\nTablica wy-" << a << "-wana\n";
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
