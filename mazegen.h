#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <tempprint.h>

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

    MazeGen(int **adress, int mazeH, int mazeW, int difficulty);
    ~MazeGen();
    int generateMaze(int startingRow);

private:

    Borders **bordersTab;
    bool **visitedTab;
    int **mazeTab;

    int mazeHeight, mazeWidth, minLength, maxLength;

    bool findNextPoint(PointXY &currentPos);
    void makeStartingPath(PointXY currentPos, int &counter, bool &a);
    void makeRandomPath(PointXY &currentPos, char direction);
    char randomDirection(PointXY currentPos);

    void rewriteTab();
    void createVisitedTab();

    void tempDiff(int difficulty); //
    void reserveBordersMemory ();
    void clearBordersMemory ();
    void reserveBoolMemory (bool **&adress, int w, int k);
    void clearBoolMemory (bool **&adress, int w);
    void resetBordersTab(); //
    void resetVisitedTab(); //
};

#endif // MAZEGEN_H
