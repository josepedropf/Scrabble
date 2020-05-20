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
    // Takes the words from the Dictionary (Words.txt) and puts them in a vector possible_words
    void Coordinates(vector <vector<char>> &gameboard, int boardsize, vector <int> npos, vector <string> possible_words,
                     int mode);
    // Asks the coordinates from the user and calls other functions like ValidPosition to ensure the viability of said coordinates
    // Also applies the function RandomWordPlacement or PlayerWord depending on the mode in use
    int MaxRange(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> gameboard);
    // Returns the maximum amount of characters a word can have 
    // considering the position and orientation previously chosen and the current state of the board 
    vector <string> MatchingWords(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                    vector <vector<char>> gameboard);
    // Returns a vector containing all words that fit the conditions (position, letters already on the board...)
    bool ValidOrientation(vector <int> numberpos, int norient, int boardsize, vector <vector<char>> gameboard);
    // Checks whether an orientation is valid having in mind the state of the board
    bool ValidWord(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> gameboard, string chosenword);
    // Checks if the word introduced by the user is able to fit the board
    bool AtLeastOneWord(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                        vector <vector<char>> gameboard);
    // Returns true if there is at least one word that fits the given criteria proving that said criteria is valid
    string GetRandomWord(vector<int> numberpos, int orient, int boardsize, vector<string> possible_words,
                         vector<vector<char>> &gameboard);
    // Choses a Random word from the vector of fitting words returned by MatchingWords
    void WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                    vector <vector<char>> &gameboard, string chword);
    // Given a word, with a valid position and orientation, the function modifies the Gameboard in order to inculde it
    void RandomWordPlacement(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                             vector <vector<char>> &gameboard);
    // Calls GetRandomWord, and then WordPlacer with the word returned by the first function
    void PlayerWord(vector <int> numberpos, int orient, int boardsize,vector <string> possible_words,
                    vector <vector<char>> &gameboard);
    // Asks the user for a word and if it is valid for the given position and orientation, calls WordPlacer
    void DrawBoard(int boardsize, vector <vector<char>> gameboard);
    // Draws the Board with the NumberCode for each spot, which other functions utilize
    // Used for Debug purposes
    // NumberCode: 
    // 0 -> Free Spot 
    // 1 -> Occupied Spot
    // 2 -> No Vertical Words Allowed and Not Suited for Starting Position
    // 3 -> No Horizontal Words Allowed and Not Suited for Starting Position
    // 4 -> No Vertical Words Allowed
    // 5 -> No Horizontal Words Allowed
    void DrawBoardClean(int boardsize,  vector <vector<char>> gameboard);
    // Draws the Board only with letters, as is intended for the user to see
    void RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> &gameboard, vector <string> possible_words);
    // Asks for the number of words to be present in the board (gives the option of a random number of words)
    // Gets Random Positions and if they are valid calls RandomWordPlacement, 
    // otherwise eliminates the invalid position from the vector of possibilities
    // Considers the Board ended if it reaches the number of words inputed by the user
    // or if there aren't more possible inital positions
    void FormatFile(int boardsize, string filename, vector<vector<char>> gameboard);
    // Saves the Board in a text file with the name given by the user


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
