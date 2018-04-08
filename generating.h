#ifndef GENERATING_H
#define GENERATING_H

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

class Generating
{
public:

    Generating(int **adress, int mazeHeight, int mazeWidth, int difficulty);
    ~Generating();
    int generateMaze(int startingRow);

private:

    Borders **bordersArray;
    bool **visitedArray;
    int **mazeArray;

    int mazeHeight, mazeWidth, minLength, maxLength;

    bool findNextPoint(PointXY &currentPos);
    void makeStartingPath(PointXY currentPos, int &counter, bool &a);
    void makeRandomPath(PointXY &currentPos, char direction);
    char randomDirection(PointXY currentPos);

    void rewriteArray();
    void createvisitedArray();

    void tempDiff(int difficulty); //
    void reserveBordersMemory ();
    void clearBordersMemory ();
    void reserveBoolMemory (bool **&adress, int w, int k);
    void clearBoolMemory (bool **&adress, int w);
    void resetbordersArray(); //
    void resetvisitedArray(); //
};

#endif // GENERATING_H
