#include <iostream>
#include <mazeclass.h>
#include <ctime>
#include <conio.h>

using namespace std;

// 201 ╔ 203 ╦ 187 ╗ //

// 204 ╠ 206 ╬ 185 ╣ //

// 200 ╚ 202 ╩ 188 ╝ //

// 186 ║ 030 _ 205 ═ //

int  main(int argc, char *argv[])
{
    srand(time(0));
    char a = 'Y';
    do
    {
        system("cls");
        MazeClass *O1;
        O1 = new MazeClass;
        delete O1;
        cout << "\nGramy od nowa? (Y/N)\n";
        a = getch();
    }
    while (a == 'y' || a == 'Y');
    return 0;
}
