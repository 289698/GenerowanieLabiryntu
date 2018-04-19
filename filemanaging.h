#ifndef FILEMANAGING_H
#define FILEMANAGING_H

#include <fstream>

using namespace std;

class FileManaging
{
public:

    FileManaging();
    void saveMaze(int **mazeArray, int mazeHeight, int mazeWidth, string fileName);
    void loadMaze(int **&mazeArray, int &mazeHeight, int &mazeWidth, string fileName);

protected:

private:

};

#endif // FILEMANAGING_H
