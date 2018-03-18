#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Borders
{
    bool *N;
    bool *E;
    bool *S;
    bool *W;
};

struct PointXY
{
    int row;
    int col;
};

class MazeGen
{
public:

    MazeGen(int **adress, int mazeH, int mazeW);
    ~MazeGen();
    void generateMaze();

private:

    Borders **bordersTab;
    bool **visitedTab;
    int **mazeTab;

    LARGE_INTEGER uTicks;
    LARGE_INTEGER uFreq;
    double ticks, freq;

    int mazeHeight, mazeWidth;

    bool findNextPoint(PointXY &currentPos);
    void makeStartingPath(PointXY currentPos, int &counter, bool &a);
    void makeRandomPath(PointXY &currentPos, char direction);
    char randomDirection(PointXY currentPos);

    void rewriteTab();
    void createVisitedTab();

    void reserveBordersMemory ();
    void clearBordersMemory ();
    void reserveBoolMemory (bool **&adress, int w, int k);
    void clearBoolMemory (bool **&adress, int w);
    void resetBordersTab(); //
};

#endif // MAZEGEN_H
