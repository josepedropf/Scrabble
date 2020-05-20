#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
using namespace std;

// The Descriptions (Comments) of the Functions are on the Header Files
int main()
{
    int mode = 1;
    bool end = false;
    string rr;
    string savefile;
    vector<string> possible_words;
    vector<int> npos(2, 0);
    vector<vector<char>> gameboard;
    int boardsize = 0;
    Board board;

    board.GetWords(possible_words, gameboard); // Transfers the words from the words.txt file to the vector possible_words

    while (!end)
    {

        board.PickSize(boardsize); // Asks and gets the size of the Board
        vector<char> line;
        line.clear();
        gameboard.clear();          // Reseting of variables for when the user wants to make more than one board

        for (int i = 0; i < boardsize; i++)
        {
            line.push_back('0');
        }

        for (int i = 0; i < boardsize; i++)
        {
            gameboard.push_back(line);  // Filling the Board with characters 0, already with it's actual size
        }
        
        board.DrawBoardClean(boardsize, gameboard);

        // Choosing Modes
        cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
             << "1 -> Choose the initial coordinates for Random Words" << endl << "2 -> Random Board" << endl
             << "3 -> Choose the initial Coordinates and the Words" << endl;
        cout << "Choose the mode of Board Building (Input one of the numbers above): ";
        while (true)    // Ensuring the mod is an integer between 0 and 3
        {
            cin >> mode;
            if (cin.fail() || mode < 0 || mode > 3)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Mode!" << endl;
                cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
                     << "1 -> Choose the initial Coordinates for Random Words" << endl << "2 -> Random Board"
                     << endl << "3 -> Choose the initial Coordinates and the Words" << endl;
                cout << "Choose the mode of Board Building (Input one of the numbers above): ";
            }
            else
                break;
        }

        switch (mode)   // Calling the Board Building function correspondent to each mode
        {
            case 0:{
                break;
            }
            case 1: {
                board.Coordinates(gameboard, boardsize, npos, possible_words, mode);
                break;
            }
            case 2: {
                board.RandomBoard(boardsize, npos, gameboard, possible_words);
                break;
            }
            case 3:{
                board.Coordinates(gameboard, boardsize, npos, possible_words, mode);
                break;
            }
        }
        cout << "Do you want to save the Board in a File [Y for yes || N for no] ? ";
        while (true)    // Asking the user if he wishes to save the Board in a file and saving in the case he does
        {
            cin >> savefile;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input!" << endl;
                cout << "Do you want to save the Board in a File [Y for yes || N for no] ? ";
            }
            else
            {
                board.Lowerstr(savefile);
                if (savefile == "y")
                {
                    string filename;
                    cout << "Name of the File (without .txt) : ";
                    while (true)
                    {
                        cin >> filename;    // Giving the file a custom name
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid Input!" << endl;
                            cout << "Name of the File (without .txt) : ";
                        }
                        else
                        {
                            board.FormatFile(boardsize, filename, gameboard);
                            break;
                        }
                    }
                    break;
                }
                else
                    break;
            }
        }

        cout << "Do you want to make a different Board [Y for yes || N for no] ? ";
        while (true)    // Giving the user the possibility of doing more boards without exiting the program
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
                    end = true; // If the user wants to quit, the program ends
                    break;
                }
            }
        }
    }
}
