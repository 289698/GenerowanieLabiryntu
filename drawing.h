#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>

class Drawing
{

public:
    void drawMaze(QPainter *painter, int **mazeArray, int mazeHeight, int mazeWidth);
};
#endif // DRAWING_H
