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
    int x;
    int y;
};

class MazeGen: public MazeClass
{
public:

    MazeGen();
    ~MazeGen();
    void temp(int a); //     UWAGA !!!
    void temp2();

private:

    Borders **bordersTab;
    bool **visitedTab;

    PointXY makeRandomPath(PointXY current);
    PointXY findNextPoint(PointXY current);

    bool randomBool();
    void rewriteTab();
    void reserveBordersMemory (Borders **&adress, int w, int k);
    void clearBordersMemory (Borders **&adress, int w, int k);
};

#endif // MAZEGEN_H
