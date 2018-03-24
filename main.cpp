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
    bool a;
    do
    {
        system("cls");
        MazeClass *O1;
        O1 = new MazeClass;
        delete O1;

        char wybor;
        cout << "\nGramy od nowa (Y/N)?\n";
        do
        {
            wybor = getch();
            if (wybor == 'Y' || wybor == 'y')
                a = 1;
            else if (wybor == 'N' || wybor == 'n')
                a = 0;
        }
        while(wybor != 'Y' && wybor != 'y' && wybor != 'N' && wybor != 'n');
    }
    while (a);
    return 0;
}
