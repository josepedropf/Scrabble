#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_SCRABBLEBOARD_H
#define SCRABBLEJUNIOR_SCRABBLEBOARD_H
using namespace std;

class ScrabbleBoard{
public:
    const vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                   'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    const vector <char> upper_letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                   'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    vector<vector <char>> gameboard;
    int boardsize = 0;
    int scorechips = 0;
    vector<vector <char>> playedl;

    void OpenBoard(string filename);
    // Make a Vector Board from a Board Text File
    void DrawGameBoard(unsigned int textcolor);
    // Draws the Game Board
    void SetColor(unsigned int color);
    bool IsolatedLetter(int line, int col);
    int WLeft(int line, int col);
    int WRight(int line, int col);
    int WUp(int line, int col);
    int WDown(int line, int col);
    bool ValidPosition(int line, int col, int worientaton);
    bool ValidLetter(int line, int col, vector <char> &plrpool);
    int GetLine(string scoord);
    int GetCol(string scoord);
    string StringCoord();
    bool CompCheckLeft(int line, int col);
    bool CompCheckRight(int line, int col);
    bool CompCheckUp(int line, int col);
    bool CompCheckDown(int line, int col);
    int TurnScore(int line, int col, bool chips);
    bool PlayPossible(vector <char> plrpool);
    vector <vector<int>> IAPossibilities(vector <char> &plrpool);
    void IAPlayer(vector <char> &plrpool, vector <char> advpool, int &line, int &col);

private:

};



#endif //SCRABBLEJUNIOR_SCRABBLEBOARD_H
