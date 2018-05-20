#ifndef MAZEMANAGMENT_H
#define MAZEMANAGMENT_H

#include "generating.h"
#include "filemanagment.h"
#include "maze.h"

class MazeManagment : public Maze
{
    Q_OBJECT
public:
    MazeManagment();
    ~MazeManagment();

    void create(int height, int width, int difficulty);
    void load();
    void save();
    void saveAs();
    void openLeader();
    void deleteMaze();
    void finish();

private slots:
    void loadSlot(int height, int width);

private:
    Generating* maze_gen;
    FileManagment* file;

    void generate();
    void newMaze();
    void reset();
};

#endif // GAME_H
