#include "mazeclass.h"

MazeClass::MazeClass()
{
    // deklaracja planszy
    mainMazeTab = new MazeStruct *[w];
    for (int i=0; i<w; i++)
        mainMazeTab[i] = new MazeStruct [k];

    // granice labiryntu
    for (int i=0; i<w; i++)
    {
        *mainMazeTab[i][0].left_ = 1;
        mainMazeTab[i][k-1].right_ = 1;
    }
    for (int j=0; j<k; j++)
    {
        mainMazeTab[0][j].up_ = 1;
        mainMazeTab[w-1][j].down_ = 1;
    }

    // łączenie ścian
    for (int i=0; i<w-1; i++)
        for (int j=0; j<k-1; j++)
        {
            //mainMazeTab[i][j].down_
        }
}

MazeClass::~MazeClass()
{
    for (int i=0; i<w; i++)
        delete[] mainMazeTab[i];
    delete[] mainMazeTab;
}


//int MazeClass::druk(int *&Habadaba)

