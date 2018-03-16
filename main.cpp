#include <iostream>
#include <mazegen.h>
#include <mazeclass.h>

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
        MazeGen *O1;
        O1 = new MazeGen;
        delete O1;
        //cin >> a;
    }
    while (a);
    return 0;
}
