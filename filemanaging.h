#ifndef FILEMANAGING_H
#define FILEMANAGING_H
#include <iostream>
#include <fstream>

using namespace std;

class FileManaging
{
public:

    FileManaging();
    void saveMaze(int **mazeTab, string fileName);
    void loadMaze(int **&mazeTab);

protected:

private:

};

#endif // FILEMANAGING_H
