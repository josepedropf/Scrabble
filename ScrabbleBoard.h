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

    void OpenBoard(const string& filename);
    // Makes a vector Board from a Board Text File
    void DrawGameBoard(unsigned int color1, unsigned int color2);
    // Draws the Game Board
    void SetColor(unsigned int color);
    // Changes the Color of the Output Text
    void DrawColorList();
    // Presents a List of Colors and respective integers associated
    void CustomizeColor(unsigned int &color1, unsigned int &color2);
    // Gives the User the opportunity to pick the colors of the Output Text or leave them unchanged
    bool IsolatedLetter(int line, int col);
    // Checks if a character is an isolated letter in the Board
    // The next 4 Functions have the following possible outputs:
    // 0 -> Empty Spot || 1 -> Unused Letter || 2 -> Used Letter
    int WLeft(int line, int col);
    // Checks what character is to the left of the given coordinates
    int WRight(int line, int col);
    // Checks what character is to the right of the given coordinates
    int WUp(int line, int col);
    // Checks what character is above of the given coordinates
    int WDown(int line, int col);
    // Checks what character is below of the given coordinates
    bool ValidPosition(int line, int col, int worientaton);
    // Checks if the given coordinates correspond to a position where a letter can be played
    bool ValidLetter(int line, int col, vector <char> &plrpool);
    // Checks if the letter of the Board to which the coordinates indicate is present in the Player Pool of letters
    int GetLine(string scoord);
    // Transforms the first String coordinate into an integer
    int GetCol(string scoord);
    // Transforms the second String coordinate into an integer
    string StringCoord(bool &forceend, bool &playing);
    // Gets the user Input for the coordinates
    // The 4 Functions return true if the letter in the given coordinates 
    // only has played letters between itself and the beggining (Left and Up) or the end of the word (Right and Down)
    // depending on the direction of the word we want to analise
    bool CompCheckLeft(int line, int col);
    bool CompCheckRight(int line, int col);
    bool CompCheckUp(int line, int col);
    bool CompCheckDown(int line, int col);
    int TurnScore(int line, int col, bool chips);
    // Calculates the Score of a turn, decreasing the number of non-assigned score chips acordingly
    bool PlayPossible(vector <char> plrpool);
    // Checks whether the characters that are possible to play are present in the player pool
    // Returns true if at least one play is possible
    vector <vector<int>> IAPossibilities(vector <char> &plrpool);
    // Retruns a vector with the coordinates of the possible plays of the IA
    void IAPlayer(vector <char> &plrpool, vector <char> advpool, int &line, int &col);
    // Simulates an IA Player. Sees one round into the future and uses the best possible play
    // of the oponent in that following round as well as it's own best outcome to decide what to do
    void Logo();
    // Draws a special board that works as a logo for the game

};



#endif //SCRABBLEJUNIOR_SCRABBLEBOARD_H
