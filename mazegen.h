#ifndef MAZEGEN_H
#define MAZEGEN_H

#include "mazeclass.h"
#include "tempprint.h"

using namespace std;

class MazeGen: public MazeClass
{
public:

    MazeGen();
    ~MazeGen();
    void temp();
    bool** cos(bool a);
    void temp69();

private:

    bool **horizontalBordersTab, **verticalBordersTab, **visitedTab;
    void makeBorders();
    void optimizeTab();
};

#endif // MAZEGEN_H
