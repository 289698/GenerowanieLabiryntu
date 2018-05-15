#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QPoint>
#include <QString>

struct MazeStruct
{
    int height, width, start, end, difficulty, seconds;
    int **array;
    QPoint currentPos;
    QString name;
    bool isDefault;
};

class Maze : public QObject
{
    Q_OBJECT
public:
    explicit Maze(QObject *parent = 0);

    MazeStruct *maze;

private:

};

#endif // MAZE_H
