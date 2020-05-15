#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
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
    //string path = "C:\\Users\\Utilizador\\CLionProjects\\ScrabbleBoardBuilder\\cmake-build-debug\\";
    unsigned int text_color = 1;
    int turn = 1, turncount = 0, rranswer = 1;
    int initiald = 7, line = 0, col = 0;
    string scoord;
    bool playing = true, validp = false, rr = true;
    sb.SetColor(text_color);
    while (rr)
    {
        if (rranswer == 0)
        {
            sb.playedl.clear();
            sb.gameboard.clear();
            playing = true;
            plr.scorep1 = plr.scorep2 = plr.scorep3 = plr.scorep4 = 0;
            sb.scorechips = 0;
            pool.pool.clear();
            pool.charp1.clear();
            pool.charp2.clear();
            pool.charp3.clear();
            pool.charp4.clear();
        }
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
        plr.GetIA();
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
        vector <char> playerpool, adversariepool;
        int playerscore = 0;
        bool isia = false;
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
                    playerscore = plr.scorep1;
                    isia = plr.ia1;
                    playername = plr.pname1;
                    playerpool = pool.charp1;
                    adversariepool = pool.charp2;
                    break;
                }
                case 2:
                {
                    playerscore = plr.scorep2;
                    isia = plr.ia2;
                    playername = plr.pname2;
                    playerpool = pool.charp2;
                    if (plr.nplayers >= 3)
                        adversariepool = pool.charp3;
                    else
                        adversariepool = pool.charp1;
                    break;
                }
                case 3:
                {
                    playerscore = plr.scorep3;
                    isia = plr.ia3;
                    playername = plr.pname3;
                    playerpool = pool.charp3;
                    if (plr.nplayers >= 4)
                        adversariepool = pool.charp4;
                    else
                        adversariepool = pool.charp1;
                    break;
                }
                case 4:
                {
                    playerscore = plr.scorep4;
                    isia = plr.ia4;
                    playername = plr.pname4;
                    playerpool = pool.charp4;
                    adversariepool = pool.charp1;
                    break;
                }
            }

            cout << endl << "------------  " << playername << " TURN  " << "------------" << endl;
            cout << playername << " ---> SCORE: " << playerscore << endl;
            cout << "scorechips: " << sb.scorechips << endl;
            while (turncount < 2 && sb.PlayPossible(playerpool))
            {
                validp = false;
                sb.DrawGameBoard(text_color);
                pool.WritePlrPool(playerpool, playername);
                while (playing && !validp)
                {
                    if (isia)
                        sb.IAPlayer(playerpool, adversariepool, line, col);
                    else
                    {
                        scoord = sb.StringCoord();
                        line = sb.GetLine(scoord);
                        col = sb.GetCol(scoord);
                    }
                    if (sb.ValidLetter(line, col, playerpool))
                    {
                        sb.playedl[line][col] = '1';
                        playerscore += sb.TurnScore(line, col,true);
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
            else
            {
                if (pool.pool.size() > 0)
                    pool.ExchangeTiles(playerpool);
            }
            switch (turn)
            {
                case 1:
                {
                    plr.scorep1 = playerscore;
                    pool.charp1 = playerpool;
                    break;
                }
                case 2:
                {
                    plr.scorep2 = playerscore;
                    pool.charp2 = playerpool;
                    break;
                }
                case 3:
                {
                    plr.scorep3 = playerscore;
                    pool.charp3 = playerpool;
                    break;
                }
                case 4:
                {
                    plr.scorep4 = playerscore;
                    pool.charp4 = playerpool;
                    break;
                }
            }
            cout << endl << "------------" << endl << "Points: " << plr.scorep1 + plr.scorep2 + plr.scorep3 + plr.scorep4 << endl << "------------" << endl;
            sb.DrawGameBoard(text_color);
            pool.WritePlrPool(playerpool, playername);
            if (sb.scorechips == 0)
                playing = false;
        }
        sb.DrawGameBoard(text_color);
        cout << endl << endl << "------------" << "  GAME OVER  " << "------------" << endl;
        vector <vector<int>> points;
        vector <int> numberpoints;
        numberpoints = {1, plr.scorep1};
        points.push_back(numberpoints);
        numberpoints = {2, plr.scorep2};
        points.push_back(numberpoints);
        if (plr.nplayers >= 3)
        {
            numberpoints = {3, plr.scorep3};
            points.push_back(numberpoints);
        }
        if (plr.nplayers >= 4)
        {
            numberpoints = {4, plr.scorep4};
            points.push_back(numberpoints);
        }
        sort(points.begin(), points.end(),
                [](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
        cout << endl << endl << endl;
        vector <string> places = {"First Place: ", "Second Place:", "Third Place: ", "Fourth Place:"};
        string iastring = " [IA Player] ", winnername = plr.pname1, winnerias = iastring;
        int winnerp = 0;
        for (int i = 0; i < points.size(); i++)
        {
            switch (points[i][0])
            {
                case 1:
                {
                    isia = plr.ia1;
                    playername = plr.pname1;
                    break;
                }
                case 2:
                {
                    isia = plr.ia2;
                    playername = plr.pname2;
                    break;
                }
                case 3:
                {
                    isia = plr.ia3;
                    playername = plr.pname3;
                    break;
                }
                case 4:
                {
                    isia = plr.ia4;
                    playername = plr.pname4;
                    break;
                }
            }
            if (isia)
                iastring = " [IA Player] ";
            else
                iastring = " [Human Player] ";
            if (i == 0)
            {
                winnername = playername;
                winnerias = iastring;
                winnerp = points[i][1];
            }
            cout << places[i] << iastring << playername << " with " << points[i][1] << " Points." << endl;
        }

        cout << endl << "THE WINNER IS " << winnername << winnerias << "WITH " << winnerp << " POINTS!";
        cout << endl << endl << "------------" << " THE END  " << "------------" << endl;

        while (true)
        {
            cout << endl << "Do you want to Restart? [0 for No || Any other number for Yes] ";
            cin >> rranswer;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Answer (it has to be a Number)! " << endl;
            }
            else
                break;
        }
        if (rranswer == 0)
            rr = false;
        rranswer = 0;
    }
    }
