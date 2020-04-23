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
vector <vector<string>> board;

void Letter_to_Int_Pos(vector <int> &numberpos, string normalpos)
{
    string lowerpos = normalpos;
    for (int i=0; i < normalpos.size(); i++)
    {
        lowerpos[i] = tolower(int(normalpos[i]));
    }

    for (int a=0; a < lowerpos.size(); a++)
    {
        for (int b=0; b < lower_letters.size(); b++)
        {
            if (lowerpos[a] == lower_letters[b])
            {
                numberpos[a] = b;
            }
        }
    }
}

bool ValidPos(vector <int> numberpos, int bsize)
{
    if (numberpos[0] < bsize && numberpos[1] < bsize && board[numberpos[0]][numberpos[1]] == "00")
        return true;
    else
        return false;
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

    vector <string> line(boardsize, "00");

    for (int i = 0; i < boardsize; i++)
    {
        board.push_back(line);
    }

    bool empty_board = true;

    while (pos != "end" || empty_board)
    {
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
                        board[npos[0]][npos[1]] = "11";
                        break;
                    }
                }
            }
        if (pos != "end")
        {
            cout << endl << "Valid Position!" << endl;
            cout << "Introduce the word orientation (H for Horizontal || V for Vertical): ";
            while(1)
            {
                cin >> orientation;
                if (cin.fail() || (orientation != lower_letters[7] && orientation != lower_letters[21] && orientation != upper_letters[7] && orientation != upper_letters[21]))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Introduce the word orientation (H for Horizontal || V for Vertical): ";
                } 
                else
                {
                    if (orientation == 'h' || orientation == 'H')
                        numborient = 0;
                    else
                        numborient = 1;
                    // WordPlacer
                    break;
                }
            }
        }
    }
    cout << "done";
}
