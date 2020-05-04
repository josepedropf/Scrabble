//
// Created by Fred on 04/05/2020.
//
#include <string>
#include <vector>
using namespace std;
#ifndef SCRABBLEBOARDBUILDER_BOARD_H
#define SCRABBLEBOARDBUILDER_BOARD_H


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
    bool ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> boardd);
    void PickSize(int &boardsize);
    bool EmptySpot(vector <vector<char>> boardd, int boardsize);
    void GetWords(vector <string> &possible_words, vector <vector<char>> boardd);
    void Coordinates(vector <vector<char>> boardd, int boardsize, vector <int> npos, vector <string> possible_words
            , int mode);
    int WordsRange(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                   vector <vector<char>> boardd, vector <string> &wordsrange);
    bool ValidOrientation(vector <int> numberpos, int n_orient, int boardsize, vector <vector<char>> boardd);
    bool ValidWord(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> boardd, string chosenword);
    bool AtLeastOneWord(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                        vector <vector<char>> boardd);
    string GetRandomWord(vector<int> numberpos, int orient, int boardsize, vector<string> possible_words,
                         vector<vector<char>> &boardd);
    void WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                    vector <vector<char>> &boardd, string chword);
    void RandomWordPlacement(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                             vector <vector<char>> &boardd);
    void PlayerWord(vector <int> numberpos, int orient, int boardsize,vector <string> possible_words,
                    vector <vector<char>> &boardd);
    void DrawBoard(int boardsize, vector <vector<char>> boardd);
    void DrawBoardClean(int boardsize,  vector <vector<char>> boardd);
    void RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> boardd, vector <string> possible_words);
    void FormatFile(int boardsize, string filename, vector<vector<char>> boardd);


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
