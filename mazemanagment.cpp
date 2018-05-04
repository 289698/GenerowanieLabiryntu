#include "mazemanagment.h"

MazeManagment::MazeManagment()
{
    maze = new MazeStruct;
    reset();
}

MazeManagment::~MazeManagment()
{
    deleteMaze();
    delete maze;
}

void MazeManagment::load()
{
    file = new FileManagment;
    connect (file, SIGNAL(loadSignal(int, int)), this, SLOT(loadSlot(int, int)));
    file->load();
    delete file;
}

void MazeManagment::loadSlot(int height, int width)
{
    deleteMaze();
    maze->height = height;
    maze->width = width;
    newMaze();
    file->maze = maze;
}

void MazeManagment::save()
{
    file = new FileManagment;
    file->maze = maze;
    if (maze->name.isEmpty())
        file->saveAs();
    else
        file->save();
    delete file;
}

void MazeManagment::saveAs()
{
    file = new FileManagment;
    file->maze = maze;
    file->saveAs();
    delete file;
}

void MazeManagment::create(int height, int width, int difficulty)
{
    deleteMaze();
    maze->height = height;
    maze->width = width;
    maze->difficulty = difficulty;
    newMaze();
    generate();
}

void MazeManagment::generate()
{
    mazeGen = new Generating(maze->array, maze->height, maze->width, maze->difficulty);
    mazeGen->generateMaze(maze->start, maze->end);
    delete mazeGen;
    maze->currentPos.setX(0);
    maze->currentPos.setY(maze->start);
}

void MazeManagment::newMaze()
{
    if (maze->array != NULL)
        return;

    maze->array = new int *[maze->height];
    for (int i=0; i<maze->height; i++)
        maze->array[i] = new int [maze->width];
}

void MazeManagment::deleteMaze()
{
    if (maze->array == NULL)
        return;

    for (int i=0; i<maze->height; i++)
        delete[] maze->array[i];
    delete maze->array;

    reset();
}

void MazeManagment::reset()
{
    maze->height = 0;
    maze->width = 0;
    maze->start = 0;
    maze->end = 0;
    maze->difficulty = 0;
    maze->array = NULL;
    maze->currentPos.setX(0);
    maze->currentPos.setY(0);
    maze->seconds = 0;
    maze->name = QString::null;
}
