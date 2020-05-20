#include "ScrabbleBoard.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
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

// 0 -> Vertical
// 1 -> Horizontal

void ScrabbleBoard::OpenBoard(const string& filename)
{
    gameboard.clear();
    vector <int> linepos, colpos, orient;
    vector <char> boardline;
    vector <string> words;
    string word;
    ifstream boardfile;
    string txtfilename = filename + ".txt";
    boardfile.open(txtfilename);
    string line;
    getline(boardfile, line);
    if (line[1] == 'x')
        boardsize = line[0];
    else
    {
        string bs = line.substr(0, 2);
        boardsize = stoi(bs);
    }
    while (true)
    {
        getline(boardfile, line);
        if (line.empty())
            break;
        else
        {
            scorechips ++;
            for (int i = 0; i < lower_letters.size(); i++)
            {
                if (lower_letters[i] == line[1])
                    colpos.push_back(i);
                if (upper_letters[i] == line[0])
                    linepos.push_back(i);
            }
            if (line[3] == 'H')
                orient.push_back(1);
            else
                orient.push_back(0);
            word.clear();
            for (int i = 5; i < line.size(); i++)
            {
                word.push_back(line[i]);
            }
            words.push_back(word);
        }
    }
    for (int i = 0; i < boardsize; i++)
    {
        boardline.push_back('0');
    }

    for (int i = 0; i < boardsize; i++)
    {
        gameboard.push_back(boardline);
        playedl.push_back(boardline);
    }

    for (int i = 0; i < linepos.size(); i++)
    {
        string wrd = words[i];
        for (int a = 0; a < wrd.size(); a++)
        {
            switch (orient[i])
            {
                case 0:
                {
                    gameboard[linepos[i] + a][colpos[i]] = wrd[a];
                    break;
                }
                case 1:
                {
                    gameboard[linepos[i]][colpos[i] + a] = wrd[a];
                    break;
                }
            }
        }
    }
    boardfile.close();
}

void ScrabbleBoard::SetColor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

void ScrabbleBoard::DrawColorList()
{
    cout << endl << "Color List: " << endl;
    cout << endl << "Black -> 0" << endl << "Blue -> 1" << endl << "Green -> 2" << endl << "Cyan -> 3" <<
         endl << "Magenta -> 5" << endl << "Brown -> 6" << endl << "Light Gray -> 7" << endl << "Dark Gray -> 8" <<
         endl << "Light Blue -> 9" << endl << "Light Green -> 10" << endl << "Light Cyan -> 11" <<
         endl << "Light Magenta -> 13" << endl << "Yellow -> 14" << endl << "White -> 15" << endl;
}

void ScrabbleBoard::CustomizeColor(unsigned int &color1, unsigned int &color2)
{
    int custc = 0;
    while(true)
    {
        cout << endl << "Do you want to customize the game's colors? [0 for No || Any other number for Yes] ";
        cin >> custc;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid Answer (it has to be a Number)! " << endl;
        }
        else
            break;
    }
    if (custc != 0)
    {
        while (true)
        {
            DrawColorList();
            cout << endl << "Customizing Main Color. Choose a Color from the List Above!" << endl;
            cin >> color1;
            if (cin.fail() || color1 == 4 || color1 == 12 || color1 < 0 || color1 > 15)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Answer (it has to be a Number on the List)! " << endl;
            }
            else
                break;
        }
        while (true)
        {
            DrawColorList();
            cout << endl << "Customizing Secondary Color. Choose a Color from the List Above!" << endl;
            cin >> color2;
            if (cin.fail() || color2 == 4 || color2 == 12 || color2 < 0 || color2 > 15)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Answer (it has to be a Number on the List)! " << endl;
            }
            else
                break;
        }
    }
}

void ScrabbleBoard::DrawGameBoard(unsigned int color1, unsigned int color2)
{
    unsigned int chcolor;
    char drawch;
    cout << endl << "   ";
    for (int i = 0; i < boardsize; i++)
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int a = 0; a < boardsize; a++)
    {
        cout << upper_letters[a] << "  ";
        for (int b = 0; b < boardsize; b++)
        {
            if (playedl[a][b] == '1')
                chcolor = 4;
            else
                chcolor = color2;
            SetColor(chcolor);
            drawch = ' ';
            if (gameboard[a][b] != '0')
                drawch = gameboard[a][b];
            cout << drawch << "  ";
            SetColor(color2);
        }
        SetColor(color1);
        cout << endl;
    }
    cout << endl << endl;
}


int ScrabbleBoard::WLeft(int line, int col)
{
    if (col != 0)
    {
        if (gameboard[line][col - 1] == '0')
            return 0;
        else if (playedl[line][col - 1] == '1')
            return 2;
        else
            return 1;
    }
    else
        return 0;
}

int ScrabbleBoard::WRight(int line, int col)
{
    if (col < boardsize - 1)
    {
        if (gameboard[line][col + 1] == '0')
            return 0;
        else if (playedl[line][col + 1] == '1')
            return 2;
        else
            return 1;
    }
    else
        return 0;
}

int ScrabbleBoard::WUp(int line, int col)
{
    if (line != 0)
    {
        if (gameboard[line - 1][col] == '0')
            return 0;
        else if (playedl[line - 1][col] == '1')
            return 2;
        else
            return 1;
    }
    else
        return 0;
}

int ScrabbleBoard::WDown(int line, int col)
{
    if (line < boardsize - 1)
    {
        if (gameboard[line + 1][col] == '0')
            return 0;
        else if (playedl[line + 1][col] == '1')
            return 2;
        else
            return 1;
    }
    else
        return 0;
}

bool ScrabbleBoard::IsolatedLetter(int line, int col)
{
    return WLeft(line, col) + WRight(line, col) + WUp(line, col) + WDown(line, col) == 0;
}

bool ScrabbleBoard::ValidPosition(int line, int col, int worientation)
{
    if (gameboard[line][col] != '0' && (worientation != 2 || playedl[line][col] != '1'))
    {
        if (IsolatedLetter(line, col))
            return true;
        if (worientation != 1 && (WLeft(line, col) == 0 && WRight(line, col) != 0))
        {
            return true;
        }
        if (worientation != 0 && (WUp(line, col) == 0 && WDown(line, col) != 0))
        {
            return true;
        }
        if (worientation != 1 && WLeft(line, col) == 2)
        {
            return ValidPosition(line, col - 1, 0);
        }
        if (worientation != 0 && WUp(line, col) == 2)
        {
            return ValidPosition(line - 1, col, 1);
        }
    }
    return false;
}

bool ScrabbleBoard::ValidLetter(int line, int col, vector<char> &plrpool)
{
    int splrpool = plrpool.size();
    if (!ValidPosition(line, col, 2))
        return false;
    else
    {
        for (int i = 0; i < splrpool; i++)
        {
            if (plrpool[i] == gameboard[line][col])
            {
                plrpool.erase(plrpool.begin() + i);
                return true;
            }
        }
        return false;
    }
}

int ScrabbleBoard::GetLine(string scoord)
{
    char chline = scoord[0];
    chline = toupper(chline);
    for (int i = 0; i < upper_letters.size(); i++)
    {
        if (upper_letters[i] == chline)
            return i;
    }
    return 0;
}

int ScrabbleBoard::GetCol(string scoord)
{
    char chcol = scoord[1];
    chcol = tolower(chcol);
    for (int i = 0; i < lower_letters.size(); i++)
    {
        if (lower_letters[i] == chcol)
            return i;
    }
    return 0;
}


string ScrabbleBoard::StringCoord(bool &forceend, bool &playing)
{
    string sc;
    while (true)
    {
        cout << endl << "Coordinates must be indicated with one Capital Letter Followed by one Lowercase Letter according to the Board." << endl;
        cout << "Introduce the Coordinates [or <end> if you want to quit]: ";
        cin >> sc;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (sc == "end")
        {
            forceend = true;
            playing = false;
            break;
        }
        else if (sc.size() != 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "The Coordinates must be exactly Two Letters!" << endl;
        }
        else if (int(lower_letters[boardsize - 1]) < int(tolower(sc[0])) || int(upper_letters[boardsize - 1]) < int(toupper(sc[1])))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "The Letters must be in the Board!" << endl;
        }
        else
            break;
    }
    return sc;
}

bool ScrabbleBoard::CompCheckLeft(int line, int col)
{
    if (WLeft(line, col) == 0 && WRight(line, col) == 0)
        return false;
    else
    {
        if (WLeft(line, col) == 0)
            return true;
        else if (WLeft(line, col) == 2)
            return CompCheckLeft(line, col - 1);
        else
            return false;
    }
}

bool ScrabbleBoard::CompCheckRight(int line, int col)
{
    if (WLeft(line, col) == 0 && WRight(line, col) == 0)
        return false;
    else
    {
        if (WRight(line, col) == 0)
            return true;
        else if (WRight(line, col) == 2)
            return CompCheckRight(line, col + 1);
        else
            return false;
    }
}

bool ScrabbleBoard::CompCheckUp(int line, int col)
{
    if (WUp(line, col) == 0 && WDown(line, col) == 0)
        return false;
    else
    {
        if (WUp(line, col) == 0)
            return true;
        else if (WUp(line, col) == 2)
            return CompCheckUp(line - 1, col);
        else
            return false;
    }
}

bool ScrabbleBoard::CompCheckDown(int line, int col)
{
    if (WUp(line, col) == 0 && WDown(line, col) == 0)
        return false;
    else
    {
        if (WDown(line, col) == 0)
            return true;
        else if (WDown(line, col) == 2)
            return CompCheckDown(line + 1, col);
        else
            return false;
    }
}

int ScrabbleBoard::TurnScore(int line, int col, bool chips)
{
    int tscore = 0;
    if (IsolatedLetter(line, col))
    {
        tscore = 1;
    }
    else
    {
        if (CompCheckLeft(line, col) && CompCheckRight(line, col))
            tscore += 1;
        if (CompCheckUp(line, col) && CompCheckDown(line, col))
            tscore += 1;
    }
    if (chips)
        scorechips -= tscore;
    return tscore;
}

bool ScrabbleBoard::PlayPossible(vector<char> plrpool)
{
    vector <char> validl;
    for (int a = 0; a < boardsize; a++)
    {
        for (int b = 0; b < boardsize; b++)
        {
            if (ValidPosition(a, b, 2))
                validl.push_back(gameboard[a][b]);
        }
    }
    if (validl.empty())
        return false;
    int sizepp = plrpool.size();
    int sizevl = validl.size();
    for (int c = 0; c < sizepp; c++)
    {
        for (int d = 0; d < sizevl; d++)
        {
            if (plrpool[c] == validl[d])
                return true;
        }
    }
    return false;
}

vector <vector<int>> ScrabbleBoard::IAPossibilities(vector<char> &plrpool)
{
    vector <vector<int>> allp;
    vector <int> coordp;
    for (int a = 0; a < boardsize; a++)
    {
        for (int b = 0; b < boardsize; b++)
        {
            if (ValidPosition(a, b, 2))
            {
                for (char c : plrpool)
                {
                    coordp.clear();
                    if (gameboard[a][b] == c)
                    {
                        coordp.push_back(a);
                        coordp.push_back(b);
                        allp.push_back(coordp);
                        break;
                    }
                }
            }
        }
    }
    return allp;
}

void ScrabbleBoard::IAPlayer(vector<char> &plrpool, vector<char> advpool, int &line, int &col)
{
    vector <vector<int>> pplays = IAPossibilities(plrpool);
    vector <vector<int>> future = IAPossibilities(advpool);
    int iascore = 0, maxiascore = 0;
    int advscore = 0, maxadvscore = 0;
    int bestplay = 0;
    vector <int> allscores;
    int pplayssize = pplays.size();
    int futsize = future.size();
    for (int i = 0; i < pplayssize; i++)
    {
        iascore = TurnScore(pplays[i][0], pplays[i][1], false);
        for (int i = 0; i < futsize; i++)
        {
            advscore = TurnScore(future[i][0], future[i][1], false);
            if (advscore > maxadvscore)
                maxadvscore = advscore;
        }
        iascore -= 0.5 * maxadvscore;
        if (iascore >= maxiascore)
        {
            maxiascore = iascore;
            bestplay = i;
        }
    }
    line = pplays[bestplay][0];
    col = pplays[bestplay][1];
}

void ScrabbleBoard::Logo()
{
    int logosize = 15;
    char drawch;
    vector <vector<char>> logo =    {{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                                     {'0', '0', 'F', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                                     {'S', 'C', 'R', 'A', 'B', 'B', 'L', 'E', '0', 'J', 'U', 'N', 'I', 'O', 'R'},
                                     {'0', '0', 'E', '0', '0', '0', '0', '0', '0', 'O', '0', '0', '0', '0', '0'},
                                     {'0', '0', 'D', '0', '0', '0', '0', '0', '0', 'S', '0', '0', '0', '0', '0'},
                                     {'0', 'F', 'E', 'U', 'P', '0', '0', '0', '0', 'E', '0', '0', '0', '0', '0'},
                                     {'0', '0', 'R', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                                     {'0', 'M', 'I', 'E', 'I', 'C', '0', '0', '0', 'P', 'R', 'O', 'G', '0', '0'},
                                     {'0', '0', 'C', '0', '0', '0', '0', '0', '0', 'E', '0', '0', '0', '0', '0'},
                                     {'0', '0', 'O', '0', '0', '0', '0', '0', '0', 'D', '0', '0', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0', '0', '0', '0', '0', 'R', '0', '0', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0', '0', '0', '0', '0', 'O', '0', '0', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                                     {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}};
    cout << "Welcome to " << endl;
    cout << endl << "   ";
    for (int i = 0; i < logosize; i++)
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int a = 0; a < logosize; a++)
    {
        cout << upper_letters[a] << "  ";
        for (int b = 0; b < logosize; b++)
        {
            SetColor(1);
            drawch = ' ';
            if (isalpha(logo[a][b]))
                drawch = logo[a][b];
            if (a == 3)
                SetColor(4);
            else if ((a == 6 && b != 9) || a == 8)
                SetColor(2);
            else
                SetColor(11);
            cout << drawch << "  ";
            SetColor(1);
        }
        cout << endl;
    }
    cout << endl << endl;
}
