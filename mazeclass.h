#ifndef MAZECLASS_H
#define MAZECLASS_H

#include <iostream>
#include <windows.h>

using namespace std;

class MazeClass
{
public:

    MazeClass();
    ~MazeClass();

protected:

    int mazeHeight;
    int mazeWidth;
    int **mazeTab;

    void reserveIntMemory (int **&adress, int w, int k);
    void clearIntMemory (int **&adress, int w);
    void reserveBoolMemory (bool **&adress, int w, int k);
    void clearBoolMemory (bool **&adress, int w);

private:

    int getIntValue();

};

#endif // MAZECLASS_H
