#include "filemanaging.h"

FileManaging::FileManaging()
{

}

void FileManaging::saveMaze(int **mazeTab, int mazeHeight, int mazeWidth, string fileName)
{
    fileName += ".txt";
    ofstream sFile(fileName.c_str());

    sFile << mazeHeight << " " << mazeWidth;
    for(int i=0; i<mazeHeight; i++)
        for(int j=0; j<mazeWidth; j++)
            sFile << " " << mazeTab[i][j];

    sFile.close();
}
