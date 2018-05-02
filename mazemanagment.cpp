#include "mazemanagment.h"

MazeManagment::MazeManagment()
{
    maze.array = NULL;
    maze.mazeName = "4444";
}

MazeManagment::~MazeManagment()
{
    deleteMaze();
}

void MazeManagment::createMaze(int height, int width, int difficulty)
{
    deleteMaze();
    maze.height = height;
    maze.width = width;
    maze.difficulty = difficulty;
    newMaze();
    generateMaze();
}

void MazeManagment::generateMaze()
{
    mazeGen = new Generating(maze.array, maze.height, maze.width, maze.difficulty);
    mazeGen->generateMaze(maze.start, maze.end);
    delete mazeGen;
    maze.currentPos.setX(0);
    maze.currentPos.setY(maze.start);
}

void MazeManagment::newMaze()
{
    if (maze.array != NULL)
        return;

    maze.array = new int *[maze.height];
    for (int i=0; i<maze.height; i++)
        maze.array[i] = new int [maze.width];
}

void MazeManagment::deleteMaze()
{
    if (maze.array == NULL)
        return;

    for (int i=0; i<maze.height; i++)
        delete[] maze.array[i];
    delete maze.array;

    maze.height = 0;
    maze.width = 0;
    maze.start = 0;
    maze.end = 0;
    maze.difficulty = 0;
    maze.array = NULL;
}
