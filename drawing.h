#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>

class Drawing
{
public:
    Drawing();
    ~Drawing();

    void drawMaze(QPainter *painter);
};

#endif // DRAWING_H
