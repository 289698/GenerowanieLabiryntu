#ifndef MAZESTRUCT_H
#define MAZESTRUCT_H

#include <QPoint>
#include <QString>

struct MazeStruct
{
    int height, width, start, end, difficulty;
    int **array;
    QPoint currentPos;
    double seconds = 0;
    QString mazeName;
};

#endif // MAZESTRUCT_H
