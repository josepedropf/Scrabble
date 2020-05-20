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
    unsigned int mtextcolor = 1, stextcolor = 2;
    int turn, turncount = 0, rranswer = 1;
    int initiald = 7, line = 0, col = 0;
    string scoord;
    bool playing = true, validp, rr = true, forceend = false;
    sb.SetColor(mtextcolor);
    while (rr)
    {
        if (rranswer == 0)
        {
            plr.scorep1 = plr.scorep2 = plr.scorep3 = plr.scorep4 = 0;
            sb.gameboard.clear();
            playing = true;
            forceend = false;
            sb.playedl.clear();
            sb.scorechips = 0;
            pool.pool.clear();
            pool.charp1.clear();
            pool.charp2.clear();
            pool.charp3.clear();
            pool.charp4.clear();
            plr.ia1 = plr.ia2 = plr.ia3 = plr.ia4 = false;
        }
        sb.Logo();
        cout << endl << "What's the path or name of the Board File (without .txt) : ";
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
            fstream Bfile(filen + ".txt");
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
        sb.DrawGameBoard(mtextcolor, stextcolor);
        pool.InitialPool(sb.gameboard, sb.boardsize, mtextcolor, stextcolor);
        sb.CustomizeColor(mtextcolor, stextcolor);
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
            cout << endl << "------------  ";
            sb.SetColor(11);
            cout << playername;
            sb.SetColor(mtextcolor);
            cout << "'s TURN  " << "------------" << endl;
            sb.SetColor(11);
            cout << playername;
            sb.SetColor(mtextcolor);
            cout << "'s SCORE: ";
            sb.SetColor(11);
            cout << playerscore << endl;
            sb.SetColor(mtextcolor);
            cout << "scorechips: " << sb.scorechips << endl;
            while (turncount < 2 && sb.PlayPossible(playerpool))
            {
                validp = false;
                sb.DrawGameBoard(mtextcolor, stextcolor);
                pool.WritePlrPool(playerpool, playername, mtextcolor, stextcolor);
                while (playing && !validp)
                {
                    if (isia)
                        sb.IAPlayer(playerpool, adversariepool, line, col);
                    else
                    {
                        scoord = sb.StringCoord(forceend, playing);
                        if (forceend)
                            turncount = 3;
                        line = sb.GetLine(scoord);
                        col = sb.GetCol(scoord);
                    }
                    if (sb.ValidLetter(line, col, playerpool))
                    {
                        playerscore += sb.TurnScore(line, col, true);
                        sb.playedl[line][col] = '1';
                        turncount += 1;
                        validp = true;
                    }
                    else
                    {
                        if (!forceend)
                            cout << endl << "Invalid Letter for the current Board Layout!" << endl;       
                    }
                }
            }

            if (turncount != 0 && !forceend)
            {
                pool.DrawPoolTurn(playerpool, min(turncount, pool.pool.size()));
            }
            else
            {
                if (!pool.pool.empty())
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

            if (sb.scorechips == 0)
                playing = false;
        }

        if (!forceend)
        {
            string fplayername, winnername;
            bool draw = false;
            vector <string> places = {"First Place:  ", "Second Place: ", "Third Place:  ", "Fourth Place: "};
            vector <vector<int>> points;
            plr.fscorep1 = {1, plr.scorep1};
            plr.fscorep2 = {2, plr.scorep2};
            plr.fscorep3 = {3, plr.scorep3};
            plr.fscorep4 = {4, plr.scorep4};
            points.push_back(plr.fscorep1);
            points.push_back(plr.fscorep2);
            if (plr.nplayers >= 3)
                points.push_back(plr.fscorep3);
            if (plr.nplayers >= 4)
                points.push_back(plr.fscorep4);

            sort(points.begin(), points.end(), [] (const vector <int> &v1, const vector <int> &v2)
            {
                return v1[1] > v2[1];
            });

            for (int i = 0; i <points.size() - 1; i++)
            {
                if (points[i][1] == points[i + 1][1])
                    places[i + 1] = places[i];
            }

            for (int i = 0; i < points.size(); i++)
            {
                switch (points[i][0])
                {
                    case 1:
                    {
                        fplayername = plr.pname1;
                        break;
                    }
                    case 2:
                    {
                        fplayername = plr.pname2;
                        break;
                    }
                    case 3:
                    {
                        fplayername = plr.pname3;
                        break;
                    }
                    case 4:
                    {
                        fplayername = plr.pname4;
                        break;
                    }
                }

                if (i == 0)
                    winnername = fplayername;
                cout << endl << places[i];
                sb.SetColor(11);
                cout << fplayername;
                sb.SetColor(mtextcolor);
                cout << " with ";
                sb.SetColor(11);
                cout << points[i][1];
                sb.SetColor(mtextcolor);
                cout << " Points." << endl;
            }

            draw = places[0] == places[1];

            if (!draw)
            {
                cout << endl << "---------------  ";
                sb.SetColor(11);
                cout << winnername;
                sb.SetColor(mtextcolor);
                cout << " WINS!!!" << "  ---------------" << endl;
            }
            else
                cout << endl << "---------------  " << "DRAW" << "  ---------------" << endl;
        }

        cout << endl << "END";

        while(true)
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
