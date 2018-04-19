#include "filemanaging.h"

FileManaging::FileManaging()
{

}

void FileManaging::saveMaze(int **mazeArray, int mazeHeight, int mazeWidth, string fileName)
{
    fileName += ".txt";
    ofstream sFile(fileName.c_str());

    sFile << mazeHeight << " " << mazeWidth;
    for(int i=0; i<mazeHeight; i++)
        for(int j=0; j<mazeWidth; j++)
            sFile << " " << mazeArray[i][j];

    sFile.close();
}

void FileManaging::loadMaze(int **&mazeArray, int &mazeHeight, int &mazeWidth, string fileName)
{
    fileName += ".txt";
    ifstream lFile(fileName.c_str());

    lFile >> mazeHeight >> mazeWidth;
    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
            lFile >> mazeArray[i][j];

    lFile.close();
}
