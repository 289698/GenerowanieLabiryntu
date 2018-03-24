#include "filemanaging.h"

FileManaging::FileManaging()
{

}

void FileManaging::saveMaze(int **mazeTab, string fileName)
{
    fileName += ".txt";
    ofstream sFile(fileName.c_str());

    sFile.close();
}
