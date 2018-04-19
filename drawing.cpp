#include "drawing.h"

void Drawing::drawMaze(QPainter *painter, int **mazeArray, int mazeHeight, int mazeWidth)
{
    if (mazeArray == NULL)
        return;

    for (int i=0; i<mazeHeight; i++)
        for (int j=0; j<mazeWidth; j++)
        {
            if(mazeArray[i][j] & 1)
                painter->drawLine(i, j, i, j+10);
            if(mazeArray[i][j] & 8)
                painter->drawLine(i, j, i+10, j);
        }
}
