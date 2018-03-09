#ifndef MAZECLASS_H
#define MAZECLASS_H

#include <iostream>

using namespace std;

class MazeClass
{
public:

    struct MazeStruct
    {
        bool *up_;
        bool *down_;
        bool *right_;
        bool *left_;
    };

    MazeClass();
    ~MazeClass();

private:

    MazeStruct **mainMazeTab;
    int w;
    int k;

};

#endif // MAZECLASS_H
