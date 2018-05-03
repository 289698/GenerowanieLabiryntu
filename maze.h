#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QPoint>
#include <QString>

struct MazeStruct
{
    int height, width, start, end, difficulty;
    int **array;
    QPoint currentPos;
    double seconds;
    QString name;
};

class Maze : public QObject
{
    Q_OBJECT
public:
    explicit Maze(QObject *parent = 0);

    MazeStruct *maze;

signals:

public slots:
};

#endif // MAZE_H
