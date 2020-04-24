#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <ctime>
#include <iomanip>
#include <fstream>

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

int boardsize = 0, numborient = 0;
string pos;
char orientation;
vector <int> npos(2, 0);
vector <string> possible_words;
vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector <char> upper_letters;
vector <vector<char>> board;

void Lowerstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = tolower(int(astring[i]));
    }
}

void Upperstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = toupper(int(astring[i]));
    }
}

bool IsLetter(char ch)
{
    for (int i = 0; i < lower_letters.size(); i++)
    {
        if (ch == lower_letters[i] || ch == upper_letters[i])
            return true;
    }
    return false;
}

void Letter_to_Int_Pos(vector <int> &numberpos, string strpos)
{
    Lowerstr(strpos);
    int copyv = 0;
    for (int a=0; a < strpos.size(); a++)
    {
        for (int b=0; b < lower_letters.size(); b++)
        {
            if (strpos[a] == lower_letters[b])
            {
                numberpos[a] = b;
            }
        }
    }
}

bool ValidPos(vector <int> numberpos, int bsize)
{
    if (numberpos[0] < bsize && numberpos[1] < bsize && board[numberpos[0]][numberpos[1]] != '1' && board[numberpos[0]][numberpos[1]] != '2' && board[numberpos[0]][numberpos[1]] != '3')
        return true;
    else
        return false;
}

bool ValidOrientation(vector <int> numberpos, int n_orient)
{
    if (n_orient == 0)
    {
        if (board[numberpos[0]][numberpos[1]] == '4')
            return false;
        if (IsLetter(board[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[0] == boardsize - 1 || IsLetter(board[numberpos[0] + 1][numberpos[1]]) || board[numberpos[0] + 1][numberpos[1]] == '1' || board[numberpos[0] + 1][numberpos[1]] == '2' || board[numberpos[0] + 1][numberpos[1]] == '4')
                return false;
        }
        return true;
    }
    else
    {
        if (board[numberpos[0]][numberpos[1]] == '5')
            return false;
        if (IsLetter(board[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[1] == boardsize - 1 || IsLetter(board[numberpos[0]][numberpos[1] + 1]) || board[numberpos[0]][numberpos[1] + 1] == '1' || board[numberpos[0]][numberpos[1] + 1] == '3' || board[numberpos[0]][numberpos[1] + 1] == '5')
                return false;
        }
        return true;
    }
}

void WordPlacer(vector <vector<char>> &aboard, vector <int> numberpos, int orient)
{
    int word_index = 0;
    bool word_approved = false, word_test = false;
    string chword;
    int maxrange = boardsize - numberpos[orient];
    vector <string> words_wrange;
    int pwsize = possible_words.size();
    for (int a = 0; a < boardsize - numberpos[orient]; a++)
    {
        cout << endl << "a " << a << endl;
        if (orient == 0)
        {
            if ((aboard[numberpos[0] + a][numberpos[1]] == '1' || board[numberpos[0] + a][numberpos[1]] == '2' || board[numberpos[0] + a][numberpos[1]] == '4') && a < maxrange)
            {
                maxrange = a;
            }
        }
        if (orient == 1)
        {
            if ((aboard[numberpos[0]][numberpos[1] + a] == '1' || board[numberpos[0]][numberpos[1] + a] == '3' || board[numberpos[0]][numberpos[1] + a] == '5') && a < maxrange)
            {
                maxrange = a;
            }
        }
    }
    cout << endl << maxrange << endl;
    for (int i=0 ; i < pwsize; i++)
    {
        if (possible_words[i].size() <= maxrange)
        {
            words_wrange.push_back(possible_words[i]);
            //cout << possible_words[i] << endl;
        }
    }

    int rletter = 0;
    if (maxrange == 1)
    {
        rletter = rand() % 26;
        chword = lower_letters[rletter];
    }
    else
    {
        int wwsize = 0, sectioni = 0;
        while(1)
        {
            wwsize = words_wrange.size() / 4;
            sectioni = rand() % 4;
            word_index =  rand() % wwsize + (sectioni * wwsize);
            cout << word_index << endl;
            chword = words_wrange[word_index];
            cout << chword << endl;
            word_test = true;
            for (int i = 0; i < chword.size(); i++)
            {
                switch (orient)
                {
                    case 0:
                    {
                        if (aboard[numberpos[0] + i][numberpos[1]] != '0' && aboard[numberpos[0] + i][numberpos[1]] != '3' && aboard[numberpos[0] + i][numberpos[1]] != '5')
                        {
                            if (chword[i] != aboard[numberpos[0] + i][numberpos[1]])
                                word_test = false;
                        }
                        if (numberpos[0] + chword.size() < boardsize)
                        {
                            if (IsLetter(aboard[numberpos[0] + chword.size()][numberpos[1]]))
                                word_test = false;
                        }
                        break;
                    }
                    case 1:
                    {
                        if (aboard[numberpos[0]][numberpos[1] + i] != '0' && aboard[numberpos[0]][numberpos[1] + i] != '2' && aboard[numberpos[0]][numberpos[1] + i] != '4')
                        {
                            if (chword[i] != aboard[numberpos[0]][numberpos[1] + i])
                                word_test = false;
                        }
                        if (numberpos[1] + chword.size() < boardsize)
                        {
                            if (IsLetter(aboard[numberpos[0]][numberpos[1] + chword.size()]))
                                word_test = false;
                        }
                        break;
                    }
                }
            }
            if (word_test)
            {
                break;
            }
            else
            {
                words_wrange.erase(words_wrange.begin() + word_index);
            }
        }
    }

    for (int i = 0; i < chword.size(); i++)
    {
        switch (orient)
        {
            case 0:
            {
                aboard[numberpos[0] + i][numberpos[1]] = chword[i];
                break;
            }
            case 1:
            {
                aboard[numberpos[0]][numberpos[1] + i] = chword[i];
                break;
            }
        }
    }
    switch (orient)
    {
        case 0:
            {
            if (numberpos[0] > 0)
            {
                aboard[numberpos[0] - 1][numberpos[1]] = '1';
            }
            if (numberpos[0] + chword.size() < boardsize)
            {
                aboard[numberpos[0] + chword.size()][numberpos[1]] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[1] < boardsize - 1)
                {
                    aboard[numberpos[0] + i][numberpos[1] + 1] = '2';
                }
                if (numberpos[1] > 0)
                {
                    if (aboard[numberpos[0] + i][numberpos[1] - 1] == '0')
                        aboard[numberpos[0] + i][numberpos[1] - 1] = '4';
                    else if (aboard[numberpos[0] + i][numberpos[1] - 1] == '3' || aboard[numberpos[0] + i][numberpos[1] - 1] == '2' || aboard[numberpos[0] + i][numberpos[1] - 1] == '4' || aboard[numberpos[0] + i][numberpos[1] - 1] == '5')
                        aboard[numberpos[0] + i][numberpos[1] - 1] = '1';
                }
            }
            break;
        }
        case 1:
            {
            if (numberpos[1] > 0)
            {
                aboard[numberpos[0]][numberpos[1] - 1] = '1';
            }
            if (numberpos[1] + chword.size() < boardsize)
            {
                aboard[numberpos[0]][numberpos[1] + chword.size()] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[0] < boardsize - 1)
                {
                    aboard[numberpos[0] + 1][numberpos[1] + i] = '3';
                }
                if (numberpos[0] > 0)
                {
                    if (aboard[numberpos[0] - 1][numberpos[1] + i] == '0')
                        aboard[numberpos[0] - 1][numberpos[1] + i] = '5';
                    else if (aboard[numberpos[0] - 1][numberpos[1] + i] == '2' || aboard[numberpos[0] - 1][numberpos[1] + i] == '3')
                        aboard[numberpos[0] - 1][numberpos[1] + i] = '1';
                }
            }
            break;
        }
    }
    cout << "Selected Word: " << chword << endl;
}

void DrawBoard()
{
    cout << "   ";
    for (int i = 0; i < boardsize; i++)
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int a = 0; a < boardsize; a++)
    {
        cout << upper_letters[a] << "  ";
        for (int b = 0; b < boardsize; b++)
        {
            cout << board[a][b] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void DrawBoardClean()
{
    char drawch = ' ';
    cout << "   ";
    for (int i = 0; i < boardsize; i++)
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int a = 0; a < boardsize; a++)
    {
        cout << upper_letters[a] << "  ";
        for (int b = 0; b < boardsize; b++)
        {
            drawch = ' ';
            for (int c = 0; c < lower_letters.size(); c++)
            {
                if (board[a][b] == lower_letters[c] || board[a][b] == upper_letters[c])
                    drawch = board[a][b];
            }
            cout << drawch << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout << "Select the board size (Length of the size of the square): ";
    while(1)
    {
        cin >> boardsize;
        if (cin.fail() || boardsize < 1 || boardsize > 20)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid board size (Input a number between 1 and 20)" << endl;
            cout << "Select the board size (Length of the size of the square): ";
        }
        else
            break;
    }

    fstream wordfile;
    wordfile.open("C:\\Users\\MSI\\Desktop\\WORDS.TXT");
    //wordfile.open("WORDS.TXT");
    string content;

    while(getline(wordfile, content))
    {
        possible_words.push_back(content);
        //cout << content << endl;
    }
    wordfile.close();

    for (int i = 0; i < size(lower_letters); i++)
        upper_letters.push_back(toupper(lower_letters[i]));

    cout << " ";
    for (int i = 0; i < boardsize; i++)                                 // output lower letters column
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int i = 0; i < boardsize; i++)                                 // output upper letters column
        cout << upper_letters[i] << endl;

    vector <char> line(boardsize, '0');

    for (int i = 0; i < boardsize; i++)
    {
        board.push_back(line);
    }

    bool empty_board = true;

    while (pos != "end" || (pos == "end" && empty_board))
    {
        DrawBoardClean();
        cout << endl << endl << endl;
        DrawBoard();
        cout << endl << "Coordinates must be indicated as two letters having in base the board above." << endl;
        cout << "Introduce the coordinates of the first letter of the word (or end if you don't want to add more words to the board): ";
            while(1)
            {
                cin >> pos;
                if (pos == "end" && !empty_board)
                    break;
                if (cin.fail() || pos.size() != 2 || (pos == "end" && empty_board))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    if (pos == "end" && empty_board)
                        cout << endl << "You can't leave the board empty!";
                    cout << endl << "Coordinates must be indicated as two letters having in base the board above." << endl;
                    cout << "Introduce the coordinates of the first letter of the word (or end if you don't want to add more words to the board): ";
                }
                else
                {
                    Letter_to_Int_Pos(npos, pos);
                    if (!ValidPos(npos, boardsize))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << endl << "Coordinates must be indicated as two letters having in base the board above." << endl;
                        cout << "Introduce the coordinates of the first letter of the word (or end if you don't want to add more words to the board): ";
                    }
                    else
                    {
                        empty_board = false;
                        break;
                    }
                }
            }
        if (pos != "end")
        {
            cout << endl << "Valid Position!" << endl;
            cout << "Introduce the word orientation (H for Horizontal || V fo Vertical): ";
            while(1)
            {
                cin >> orientation;
                if (cin.fail() || (orientation != lower_letters[7] && orientation != lower_letters[21] && orientation != upper_letters[7] && orientation != upper_letters[21]))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Introduce the word orientation (H for Horizontal || V fo Vertical): ";
                }
                else
                    {
                    if (orientation == 'h' || orientation == 'H')
                        numborient = 1;
                    else
                        numborient = 0;

                    if (!ValidOrientation(npos, numborient))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << endl << "The orientation is Invalid for the position you chose previously!" << endl;
                        break;
                    }
                    else
                    {
                        WordPlacer(board, npos, numborient);
                        break;
                    }
                    }
            }
        }
    }
    cout << "done";
}
