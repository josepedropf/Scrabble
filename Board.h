#ifndef BOARDBUILDER_BOARD_H
#define BOARDBUILDER_BOARD_H
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Board {

public:
    const vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                         'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    const vector <char> upper_letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                         'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    void Lowerstr(string &astring);
    // Applies tolower to all the chars of a string
    void Upperstr(string &astring);
    // Applies toupper to all the chars of a string
    bool IsLetter(char ch);
    // Function like isalpha but also considers the char (') 
    void Letter_to_Int_Pos(vector <int> &numberpos, string normalpos);
    // Transforms a String ( two letters ) coordinate in a vector <int> coordinate
    bool ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> gameboard);
    // Checks whether a position is suitable to start a word
    void PickSize(int &boardsize);
    // Asks and gets the Size of the Board
    bool EmptySpot(vector <vector<char>> gameboard, int boardsize);
    // Retruns true if there is at least one valid position on the entire Board
    void GetWords(vector <string> &possible_words, vector <vector<char>> gameboard);
    void Coordinates(vector <vector<char>> &gameboard, int boardsize, vector <int> npos, vector <string> possible_words,
                     int mode);
    int BinarySearch(vector<string> vs, int firstelem, int lastelem, char objective, int objpos);
    int MaxRange(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> gameboard);
    vector <string> MatchingWords(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                    vector <vector<char>> gameboard);
    bool ValidOrientation(vector <int> numberpos, int norient, int boardsize, vector <vector<char>> gameboard);
    bool ValidWord(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> gameboard, string chosenword);
    bool AtLeastOneWord(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                        vector <vector<char>> gameboard);
    string GetRandomWord(vector<int> numberpos, int orient, int boardsize, vector<string> possible_words,
                         vector<vector<char>> &gameboard);
    void WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                    vector <vector<char>> &gameboard, string chword);
    void RandomWordPlacement(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                             vector <vector<char>> &gameboard);
    void PlayerWord(vector <int> numberpos, int orient, int boardsize,vector <string> possible_words,
                    vector <vector<char>> &gameboard);
    void DrawBoard(int boardsize, vector <vector<char>> gameboard);
    void DrawBoardClean(int boardsize,  vector <vector<char>> gameboard);
    void RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> &gameboard, vector <string> possible_words);
    void FormatFile(int boardsize, string filename, vector<vector<char>> gameboard);


private:
    vector <string> strcoord;
    vector <char> chorient;
    vector <string> wordlist;
    bool empty_board = true;
    string pos;
    int numborient = 0;
    char orientation;
};
#endif //BOARDBUILDER_BOARD_H
