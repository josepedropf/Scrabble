#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
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
    string path = "C:\\Users\\MSI\\CLionProjects\\BoardBuilder\\cmake-build-debug\\";
    unsigned int text_color = 1;
    int turn = 1, turncount = 0;
    int initiald = 7, line = 0, col = 0;
    string scoord;
    bool playing = true, validp = false;
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
    srand(time(0));
    turn = rand() % plr.nplayers + 1;
    string playername;
    vector <char> playerpool;
    int playerscore = 0;
    while (playing)
    {
        if (turn < plr.nplayers)
            turn ++;
        else
            turn = 1;
        turncount = 0;
        playerscore = 0;
        switch (turn)
        {
            case 1:
            {
                playername = plr.pname1;
                playerpool = pool.charp1;
                break;
            }
            case 2:
            {
                playername = plr.pname2;
                playerpool = pool.charp2;
                break;
            }
            case 3:
            {
                playername = plr.pname3;
                playerpool = pool.charp3;
                break;
            }
            case 4:
            {
                playername = plr.pname4;
                playerpool = pool.charp4;
                break;
            }
        }

        cout << endl << "------------  " << playername << " TURN  " << "------------" << endl;
        cout << playername << " ---> SCORE: " << plr.scorep1 << endl;
        while (turncount < 2 && sb.PlayPossible(playerpool))
        {
            validp = false;
            sb.DrawGameBoard(text_color);
            pool.WritePlrPool(playerpool, playername);
            while (!validp)
            {
                scoord = sb.StringCoord();
                line = sb.GetLine(scoord);
                col = sb.GetCol(scoord);
                if (sb.ValidLetter(line, col, playerpool))
                {
                    playerscore += sb.TurnScore(line, col, 2);
                    sb.playedl[line][col] = '1';
                    turncount += 1;
                    validp = true;
                }
                else
                    cout << endl << "Invalid Letter for the current Board Layout!" << endl;
            }
        }

        if (turncount != 0)
        {
            pool.DrawPoolTurn(playerpool, min(turncount, pool.pool.size()));
        }

        if (playerscore != 0)
        {
            switch (turn)
            {
                case 1:
                {
                    plr.scorep1 += playerscore;
                    pool.charp1 = playerpool;
                    break;
                }
                case 2:
                {
                    plr.scorep2 += playerscore;
                    pool.charp2 = playerpool;
                    break;
                }
                case 3:
                {
                    plr.scorep3 += playerscore;
                    pool.charp3 = playerpool;
                    break;
                }
                case 4:
                {
                    plr.scorep4 += playerscore;
                    pool.charp4 = playerpool;
                    break;
                }
            }
        }
    }
}
