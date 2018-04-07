#include "drawing.h"

Drawing::Drawing()
{

}

void Drawing::drawMaze(QPainter *painter)
{
    float A[2], B[2], C[2], P[2];
    A[0]=200; A[1]=50; B[0]=50; B[1]=250; C[0]=350; C[1]=250; P[0]=0; P[1]=0;

    painter->setPen(Qt::red);
    painter->drawLine(A[0],A[1],B[0],B[1]);
    painter->drawLine(B[0],B[1],C[0],C[1]);
    painter->drawLine(C[0],C[1],A[0],A[1]);

    painter->setPen(Qt::black);
    for (int i=0; i<100000; i++)
    {
        int losuj = floor(rand()%3);
        switch(losuj)
        {
        case 0:
            P[0]=(P[0]+A[0])/2;
            P[1]=(P[1]+A[1])/2;
            break;
        case 1:
            P[0]=(P[0]+B[0])/2;
            P[1]=(P[1]+B[1])/2;
            break;
        case 2:
            P[0]=(P[0]+C[0])/2;
            P[1]=(P[1]+C[1])/2;
            break;
        }
        painter->drawPoint(P[0],P[1]);
    }
}
