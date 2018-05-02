#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include "mazestruct.h"

class FileManagment
{
public:
    FileManagment();
    ~FileManagment();

private:
    QDir *dir;

    void loadMaze(QString fileName, MazeStruct maze);
    void saveMaze(QString fileName, MazeStruct maze);
};

#endif // FILEMANAGMENT_H
