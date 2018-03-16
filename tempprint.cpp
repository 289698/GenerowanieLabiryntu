#include "tempprint.h"

void printIntTab(int **adress, bool **adress2, int w, int k)
{
    for (int i=0; i<w; i++)
    {
        for (int j=0; j<k; j++)
        {
            if (adress2[i][j])
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

            switch (adress[i][j])
            {
            case 0:
                cout << char(206);
                break;
            case 1:
                cout << char(203);
                break;
            case 2:
                cout << char(185);
                break;
            case 3:
                cout << char(187);
                break;
            case 4:
                cout << char(202);
                break;
            case 5:
                cout << char(205);
                break;
            case 6:
                cout << char(188);
                break;
            case 7:
                cout << char(254);
                break;
            case 8:
                cout << char(204);
                break;
            case 9:
                cout << char(201);
                break;
            case 10:
                cout << char(186);
                break;
            case 11:
                cout << char(254);
                break;
            case 12:
                cout << char(200);
                break;
            case 13:
                cout << char(254);
                break;
            case 14:
                cout << char(254);
                break;
            case 15:
                cout << char(35);
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << adress[i][j];
            }
            //cout << " ";
            //cout << adress[i][j] << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        cout << endl;
    }
}
/*


*/
