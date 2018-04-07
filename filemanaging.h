#ifndef FILEMANAGING_H
#define FILEMANAGING_H
#include <iostream>
#include <fstream>

using namespace std;

class FileManaging
{
public:

    FileManaging();
    void saveMaze(int **mazeTab, int mazeHeight, int mazeWidth, string fileName);
    void loadMaze(int **&mazeTab, int mazeHeight, int mazeWidth);

protected:

private:

};

#endif // FILEMANAGING_H
