#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ScrabbleBoard.h"
#include "Pool.h"
#include "Player.h"
using namespace std;

int main()
{
    Pool pool;
    Player plr;
    ScrabbleBoard sb;
    string filen;
    string path = "C:\\Users\\MSI\\CLionProjects\\ScrabbleBoardBuilder\\cmake-build-debug\\";
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
    sb.OpenBoard(filen, sb.boardsize, sb.gameboard);
    sb.DrawGameBoard(sb.boardsize, sb.gameboard);
    pool.InitialPool(sb.gameboard, sb.boardsize, pool.pool);
}
