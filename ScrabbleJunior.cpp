#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include "ScrabbleBoard.h"
#include "Pool.h"
#include "Player.h"

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

int main()
{
    Pool pool;
    Player plr;
    ScrabbleBoard sb;
    string filen;
    string path = "C:\\Users\\MSI\\CLionProjects\\ScrabbleBoardBuilder\\cmake-build-debug\\";
    unsigned int text_color = 1;
    int turn = 1;
    int initiald = 7;
    sb.SetColor(text_color);
    cout << endl << "Welcome to Scrabble Junior!" << endl;
    cout << "What's the name of the Board File (without .txt) : ";
    while(true)
    {
        cin >> filen;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid File Name!" << endl;
            cout << "What's the name of the Board File (without .txt) : ";
        }
        fstream Bfile(path + filen + ".txt");
        if (Bfile.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid File Name!" << endl;
            cout << "What's the name of the Board File (without .txt) : ";
        }
        else
            break;
    }
    sb.OpenBoard(filen);
    sb.DrawGameBoard(text_color);
    pool.InitialPool(sb.gameboard, sb.boardsize);
    plr.GetPlayers();
    int cn = 1;
    while(true)
    {
        cout << endl << "Do you want to customize your names? [0 for No || Any other number for Yes] ";
        cin >> cn;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid Answer (it has to be a Number)! " << endl;
        }
        else
            break;
    }

    if (cn != 0)
        plr.CustomPlayerNames();

    if (pool.pool.size() >= 7 * plr.nplayers)
        initiald = 7;
    else
        initiald = pool.pool.size() / plr.nplayers;
    pool.InitialDraw(initiald, plr.nplayers);

}
