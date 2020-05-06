#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_SCRABBLEBOARD_H
#define SCRABBLEJUNIOR_SCRABBLEBOARD_H
using namespace std;

class ScrabbleBoard{
public:
    vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                   'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector <char> upper_letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                   'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    vector<vector <char>> gameboard;
    int boardsize = 0;

    void OpenBoard(string filename, int &boardsize, vector<vector <char>> &gameboard);
    // Make a Vector Board from a Board Text File
    void DrawGameBoard(int boardsize,  vector <vector<char>> gameboard);
    // Draws the Game Board
};


#endif //SCRABBLEJUNIOR_SCRABBLEBOARD_H