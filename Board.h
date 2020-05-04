#include <string>
#include <vector>
using namespace std;
#ifndef SCRABBLEBOARDBUILDER_BOARD_H
#define SCRABBLEBOARDBUILDER_BOARD_H
//#ifndef BOARDBUILDER_BOARD_H
//#define BOARDBUILDER_BOARD_H


class Board {

public:
    vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                   'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    vector <char> upper_letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                   'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    void Lowerstr(string &astring);
    void Upperstr(string &astring);
    bool IsLetter(char ch);
    void Letter_to_Int_Pos(vector <int> &numberpos, string normalpos);
    bool ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> gameboard);
    void PickSize(int &boardsize);
    bool EmptySpot(vector <vector<char>> gameboard, int boardsize);
    void GetWords(vector <string> &possible_words, vector <vector<char>> gameboard);
    void Coordinates(vector <vector<char>> &gameboard, int boardsize, vector <int> npos, vector <string> possible_words, 
                     int mode);
    int WordsRange(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                   vector <vector<char>> gameboard, vector <string> &wordsrange);
    bool ValidOrientation(vector <int> numberpos, int n_orient, int boardsize, vector <vector<char>> gameboard);
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



#endif //SCRABBLEBOARDBUILDER_BOARD_H
//#endif //BOARDBUILDER_BOARD_H
