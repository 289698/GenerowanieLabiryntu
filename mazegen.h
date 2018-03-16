#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <ctime>
#include <cstdlib>
#include "mazeclass.h"
#include "tempprint.h"

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

class MazeGen: public MazeClass
{
public:

    MazeGen();
    ~MazeGen();
    void temp(bool a); //     UWAGA !!!
    void temp2(bool clean, int sleepTime);
    void temp3();

private:

    Borders **bordersTab;
    bool **visitedTab;

    LARGE_INTEGER uTicks;
    LARGE_INTEGER uFreq;
    double ticks, freq;

    void generateMaze();
    bool findNextPoint(PointXY &currentPos);
    void makeRandomPath(PointXY currentPos);
    char randomDirection(PointXY currentPos);

    void rewriteTab();
    void reserveBordersMemory ();
    void clearBordersMemory ();
};

#endif // MAZEGEN_H
