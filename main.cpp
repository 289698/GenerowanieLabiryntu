#include <iostream>
#include <mazeclass.h>
#include <ctime>

using namespace std;

// 201 ╔ 203 ╦ 187 ╗ //

// 204 ╠ 206 ╬ 185 ╣ //

// 200 ╚ 202 ╩ 188 ╝ //

// 186 ║ 030 _ 205 ═ //

int  main(int argc, char *argv[])
{
    srand(time(0));
    bool a = 1;
    do
    {
        MazeClass *O1;
        O1 = new MazeClass;
        delete O1;
        cin >> a;
    }
    while (a);
    return 0;
}
