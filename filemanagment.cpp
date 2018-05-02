#include "filemanagment.h"


FileManagment::FileManagment()
{
    dir = new QDir;

    if (!dir->cd("saves"))
    {
        dir->mkdir("saves");
        dir->cd("saves");
    }
}

FileManagment::~FileManagment()
{
    delete dir;
}

void FileManagment::loadMaze(QString fileName, MazeStruct maze)
{
    fileName += ".txt";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in >> maze.height >> maze.width >> maze.start >> maze.end >> maze.difficulty;
    for (int i=0; i<maze.height; i++)
        for (int j=0; j<maze.width; j++)
            in >> maze.array[i][j];

    file.flush();
    file.close();
}

void FileManagment::saveMaze(QString fileName, MazeStruct maze)
{
    fileName += ".txt";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << maze.height << " " << maze.width << " " << maze.start << " " << maze.end << " " << maze.difficulty;
    for (int i=0; i<maze.height; i++)
        for (int j=0; j<maze.width; j++)
            out << " " << maze.array[i][j];

    file.flush();
    file.close();
}
