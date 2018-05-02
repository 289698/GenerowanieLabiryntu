#ifndef GAME_H
#define GAME_H

#include "generating.h"
#include "mazestruct.h"

class MazeManagment
{
public:
    MazeManagment();
    ~MazeManagment();

    MazeStruct maze;

    void createMaze(int height, int width, int difficulty);
    void deleteMaze();

private:
    Generating* mazeGen;

    void generateMaze();
    void newMaze();
};

#endif // GAME_H
