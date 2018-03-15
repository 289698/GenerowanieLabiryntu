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
    int w;
    int k;
};

class MazeGen: public MazeClass
{
public:

    MazeGen();
    ~MazeGen();
    void temp(bool a); //     UWAGA !!!
    void temp2();
    void temp3();

private:

    Borders **bordersTab;
    bool **visitedTab;
    PointXY startingPoint;

    LARGE_INTEGER uTicks;
    LARGE_INTEGER uFreq;
    double ticks, freq;

    void makeRandomPath(PointXY currentPos);
    bool findNextDir(PointXY current, char &dir, int &a);
    bool findNextPoint();

    bool randomBool();
    void rewriteTab();
    void reserveBordersMemory (Borders **&adress, int w, int k);
    void clearBordersMemory (Borders **&adress, int w, int k);
};

#endif // MAZEGEN_H
