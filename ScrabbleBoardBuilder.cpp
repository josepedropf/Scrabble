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

vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector <char> upper_letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

class Board
{
public:
    void Lowerstr(string &astring);
    void Upperstr(string &astring);
    bool IsLetter(char ch);
    void Letter_to_Int_Pos(vector <int> &numberpos, string normalpos, vector <char> lower_letters);
    bool ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> boardd);
    void PickSize(int &boardsize);
    void GetWords(vector <string> &possible_words, vector <vector<char>> boardd);
    void Coordinates(vector <char> lower_letters, vector <char> upper_letters, vector <vector<char>> boardd, int boardsize, vector <int> npos, vector <string> possible_words);
    bool ValidOrientation(vector <int> numberpos, int n_orient, int boardsize, vector <vector<char>> boardd);
    void WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words, vector <vector<char>> &boardd);
    void DrawBoard(int boardsize, vector <vector<char>> boardd);
    void DrawBoardClean(int boardsize,  vector <vector<char>> boardd);
    void RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> boardd, vector <string> possible_words);

private:
    bool empty_board = true;
    string pos;
    int numborient = 0;
    char orientation;

};

bool Board::IsLetter(char ch)
{
    for (int i = 0; i < lower_letters.size(); i++)
    {
        if (ch == lower_letters[i] || ch == upper_letters[i])
            return true;
    }
    return false;
}

void Board::Lowerstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = tolower(int(astring[i]));
    }
}

void Board::Upperstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = toupper(int(astring[i]));
    }
}

void Board::Letter_to_Int_Pos(vector <int> &numberpos, string normalpos, vector <char> lower_letters)
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

bool Board::ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> boardd)
{
    if (numberpos[0] < bsize && numberpos[1] < bsize && boardd[numberpos[0]][numberpos[1]] == '0')
        return true;
    else
        return false;
}

void Board::PickSize(int &boardsize)
{
    string rdecision = "N";
    cout << "Do you want a random board size? [Y for yes || N for no] ";
    while(1)
    {
        cin >> rdecision;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
            cout << "Do you want a random board size? [Y for yes || N for no] ";
        }
        else
            break;
    }
    Lowerstr(rdecision);

    if (rdecision == "y")
    {
        boardsize = rand() % 17 + 4;
        cout << "Board Size: " << boardsize << endl;
    }
    else
    {
        cout << "Select the board size [4 to 20] (Length of the size of the square): ";
        while(1)
        {
            cin >> boardsize;
            if (cin.fail() || boardsize < 4 || boardsize > 20)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid board size (Input a number between 4 and 20)" << endl;
                cout << "Select the board size (Length of the size of the square): ";
            }
            else
                break;
        }
    }
}

bool Board::ValidOrientation(vector <int> numberpos, int n_orient, int boardsize, vector <vector<char>> boardd)
{
    if (n_orient == 0)
    {
        if (boardd[numberpos[0]][numberpos[1]] == '4')
            return false;
        if (IsLetter(boardd[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[0] == boardsize - 1 || IsLetter(boardd[numberpos[0] + 1][numberpos[1]]) || boardd[numberpos[0] + 1][numberpos[1]] == '1' || boardd[numberpos[0] + 1][numberpos[1]] == '2' || boardd[numberpos[0] + 1][numberpos[1]] == '4')
                return false;
        }
        return true;
    }
    else
    {
        if (boardd[numberpos[0]][numberpos[1]] == '5')
            return false;
        if (IsLetter(boardd[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[1] == boardsize - 1 || IsLetter(boardd[numberpos[0]][numberpos[1] + 1]) || boardd[numberpos[0]][numberpos[1] + 1] == '1' || boardd[numberpos[0]][numberpos[1] + 1] == '3' || boardd[numberpos[0]][numberpos[1] + 1] == '5')
                return false;
        }
        return true;
    }
}

void Board::WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words, vector <vector<char>> &boardd)
{
    int word_index = 0;
    bool word_approved = false, word_test = false;
    string chword;
    int maxrange = boardsize - numberpos[orient];
    vector <string> words_wrange;
    int pwsize = possible_words.size();
    for (int a = 0; a < boardsize - numberpos[orient]; a++)
    {
        if (orient == 0)
        {
            if ((boardd[numberpos[0] + a][numberpos[1]] == '1' || boardd[numberpos[0] + a][numberpos[1]] == '2' || boardd[numberpos[0] + a][numberpos[1]] == '4') && a < maxrange)
            {
                maxrange = a;
            }
        }
        if (orient == 1)
        {
            if ((boardd[numberpos[0]][numberpos[1] + a] == '1' || boardd[numberpos[0]][numberpos[1] + a] == '3' || boardd[numberpos[0]][numberpos[1] + a] == '5') && a < maxrange)
            {
                maxrange = a;
            }
        }
    }
    cout << endl << "Max Range: " << maxrange << endl;
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
        while(words_wrange.size() > 4)
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
                        if (boardd[numberpos[0] + i][numberpos[1]] != '0' && boardd[numberpos[0] + i][numberpos[1]] != '3' && boardd[numberpos[0] + i][numberpos[1]] != '5')
                        {
                            if (chword[i] != boardd[numberpos[0] + i][numberpos[1]])
                                word_test = false;
                        }
                        if (numberpos[0] + chword.size() < boardsize)
                        {
                            if (IsLetter(boardd[numberpos[0] + chword.size()][numberpos[1]]))
                                word_test = false;
                        }
                        break;
                    }
                    case 1:
                    {
                        if (boardd[numberpos[0]][numberpos[1] + i] != '0' && boardd[numberpos[0]][numberpos[1] + i] != '2' && boardd[numberpos[0]][numberpos[1] + i] != '4')
                        {
                            if (chword[i] != boardd[numberpos[0]][numberpos[1] + i])
                                word_test = false;
                        }
                        if (numberpos[1] + chword.size() < boardsize)
                        {
                            if (IsLetter(boardd[numberpos[0]][numberpos[1] + chword.size()]))
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
    if (words_wrange.size() <= 4)
        chword = "6";
    for (int i = 0; i < chword.size(); i++)
    {
        switch (orient)
        {
            case 0:
            {
                boardd[numberpos[0] + i][numberpos[1]] = chword[i];
                break;
            }
            case 1:
            {
                boardd[numberpos[0]][numberpos[1] + i] = chword[i];
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
                boardd[numberpos[0] - 1][numberpos[1]] = '1';
            }
            if (numberpos[0] + chword.size() < boardsize)
            {
                boardd[numberpos[0] + chword.size()][numberpos[1]] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[1] < boardsize - 1)
                {
                    boardd[numberpos[0] + i][numberpos[1] + 1] = '2';
                }
                if (numberpos[1] > 0)
                {
                    if (boardd[numberpos[0] + i][numberpos[1] - 1] == '0')
                        boardd[numberpos[0] + i][numberpos[1] - 1] = '4';
                    else if (boardd[numberpos[0] + i][numberpos[1] - 1] == '3' || boardd[numberpos[0] + i][numberpos[1] - 1] == '2' || boardd[numberpos[0] + i][numberpos[1] - 1] == '4' || boardd[numberpos[0] + i][numberpos[1] - 1] == '5')
                        boardd[numberpos[0] + i][numberpos[1] - 1] = '1';
                }
            }
            break;
        }
        case 1:
        {
            if (numberpos[1] > 0)
            {
                boardd[numberpos[0]][numberpos[1] - 1] = '1';
            }
            if (numberpos[1] + chword.size() < boardsize)
            {
                boardd[numberpos[0]][numberpos[1] + chword.size()] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[0] < boardsize - 1)
                {
                    boardd[numberpos[0] + 1][numberpos[1] + i] = '3';
                }
                if (numberpos[0] > 0)
                {
                    if (boardd[numberpos[0] - 1][numberpos[1] + i] == '0')
                        boardd[numberpos[0] - 1][numberpos[1] + i] = '5';
                    else if (boardd[numberpos[0] - 1][numberpos[1] + i] == '2' || boardd[numberpos[0] - 1][numberpos[1] + i] == '3')
                        boardd[numberpos[0] - 1][numberpos[1] + i] = '1';
                }
            }
            break;
        }
    }
    cout << "Selected Word: " << chword << endl;
}

void Board::Coordinates(vector <char> lower_letters, vector <char> upper_letters, vector <vector<char>> boardd, int boardsize, vector <int> npos, vector <string> possible_words)
{
    while (pos != "end" || (pos == "end" && empty_board))
    {
        DrawBoardClean(boardsize, boardd);
        cout << endl << endl << endl;
        DrawBoard(boardsize, boardd);
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
                Letter_to_Int_Pos(npos, pos, lower_letters);
                if (!ValidPos(npos, boardsize, boardd))
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
            cout << "Introduce the word orientation (H for Horizontal || V for Vertical): ";
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

                    if (!ValidOrientation(npos, numborient, boardsize, boardd))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << endl << "The orientation is Invalid for the position you chose previously!" << endl;
                        break;
                    }
                    else
                    {
                        WordPlacer(npos, numborient, boardsize, possible_words, boardd);
                        break;
                    }
                }
            }
        }
    }
    cout << "done";
}

void Board::GetWords(vector <string> &possible_words, vector <vector<char>> boardd)
{
    fstream wordfile;
    wordfile.open("C:\\Users\\MSI\\Desktop\\WORDS.TXT");
    //wordfile.open("C:\\Users\\Utilizador\\Desktop\\WORDS.TXT");
    //wordfile.open("WORDS.TXT");
    string content;

    while(getline(wordfile, content))
    {
        possible_words.push_back(content);
        //cout << content << endl;
    }
    wordfile.close();
}

void Board::DrawBoard(int boardsize, vector <vector<char>> boardd)
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
            cout << boardd[a][b] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::DrawBoardClean(int boardsize,  vector <vector<char>> boardd)
{
    char drawch = ' ';
    cout << endl << "   ";
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
                if (boardd[a][b] == lower_letters[c] || boardd[a][b] == upper_letters[c])
                    drawch = boardd[a][b];
            }
            cout << drawch << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Board::RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> boardd, vector <string> possible_words)
{
    int nwords = rand() % (2 * boardsize) + 4;
    cout << endl << "Number of Words: " << nwords << endl;
    bool validword = false;
    int cl, cc, randomor;
    int counter = 0;
    for (int i = 0; i < nwords; i++)
    {
        validword = false;
        while (!validword)
        {
            counter++;
            cl = rand() % boardsize;
            cc = rand() % boardsize;
            npos[0] = cl;
            npos[1] = cc;
            if (ValidPos(npos, boardsize, boardd))
            {
                randomor = rand() % 2;
                if (ValidOrientation(npos, randomor, boardsize, boardd))
                {
                    WordPlacer(npos, randomor, boardsize, possible_words, boardd);
                    validword = true;
                }
                if (randomor == 0)
                    randomor = 1;
                else
                    randomor = 0;
                if (ValidOrientation(npos, randomor, boardsize, boardd))
                {
                    WordPlacer(npos, randomor, boardsize, possible_words, boardd);
                    validword = true;
                }
            }
            if (counter > 10000)
                validword = true;
        }
        DrawBoardClean(boardsize, boardd);
    }
}

int main()
{
    int mode = 1;
    bool end = false;
    string rr;
    vector<string> possible_words;
    vector<int> npos(2, 0);

    vector<vector<char>> boardd;
    int boardsize = 0;
    Board board;

    board.GetWords(possible_words, boardd);

    while (!end)
    {

        board.PickSize(boardsize);
        vector<char> line(boardsize, '0');

        for (int i = 0; i < boardsize; i++) {
            boardd.push_back(line);
        }

        cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
             << "1 -> Choose the initial coordinates for Random Words" << endl << "2 -> Totally Random Board" << endl;
        cout << "Choose the mode of Board Building (Input one of the numbers above): ";
        while (1) {
            cin >> mode;
            if (cin.fail() || mode < 0 || mode > 2) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Mode!" << endl;
                cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
                     << "1 -> Choose the initial coordinates for Random Words" << endl << "2 -> Totally Random Board"
                     << endl;
                cout << "Choose the mode of Board Building (Input one of the numbers above): ";
            } else
                break;
        }

        switch (mode)
        {
            case 0: {
                break;
            }
            case 1: {
                board.Coordinates(lower_letters, upper_letters, boardd, boardsize, npos, possible_words);
                break;
            }
            case 2: {
                board.RandomBoard(boardsize, npos, boardd, possible_words);
                break;
            }
        }
        cout << "Do you want to make a different Board [Y for yes || N for no] ? ";
        while(1)
        {
            cin >> rr;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input!" << endl;
                cout << "Do you want to make a different Board [Y for yes || N for no] ? ";
            }
            else
            {
                board.Lowerstr(rr);
                if (rr == "y")
                    break;
                else
                {
                    end = true;
                    break;
                }
            }
        }
    }
}
