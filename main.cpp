#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
using namespace std;

int main() {
    int mode = 1;
    bool end = false;
    string rr;
    string savefile;
    vector<string> possible_words;
    vector<int> npos(2, 0);
    vector<vector<char>> boardd;
    int boardsize = 0;
    Board board;

    board.GetWords(possible_words, boardd);

    while (!end)
    {

        board.PickSize(boardsize);
        vector<char> line;
        line.clear();
        boardd.clear();

        for (int i = 0; i < boardsize; i++)
        {
            line.push_back('0');
        }

        for (int i = 0; i < boardsize; i++)
        {
            boardd.push_back(line);
        }

        board.DrawBoard(boardsize, boardd);

        cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
             << "1 -> Choose the initial coordinates for Random Words" << endl << "2 -> Totally Random Board" << endl
             << "3 -> Choose the initial Coordinates and the Words" << endl;
        cout << "Choose the mode of Board Building (Input one of the numbers above): ";
        while (1)
        {
            cin >> mode;
            if (cin.fail() || mode < 0 || mode > 3)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid Mode!" << endl;
                cout << endl << "Modes: " << endl << endl << "O -> Exit" << endl
                     << "1 -> Choose the initial Coordinates for Random Words" << endl << "2 -> Totally Random Board"
                     << endl << "3 -> Choose the initial Coordinates and the Words" << endl;
                cout << "Choose the mode of Board Building (Input one of the numbers above): ";
            }
            else
                break;
        }

        switch (mode)
        {
            case 0:{
                break;
            }
            case 1: {
                board.Coordinates(boardd, boardsize, npos, possible_words, mode);
                break;
            }
            case 2: {
                board.RandomBoard(boardsize, npos, boardd, possible_words);
                break;
            }
            case 3:{
                board.Coordinates(boardd, boardsize, npos, possible_words, mode);
                break;
            }
        }
        cout << "Do you want to save the Board in a File [Y for yes || N for no] ? ";
        while(1)
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
                    while(1)
                    {
                        cin >> filename;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid Input!" << endl;
                            cout << "Name of the File (without .txt) : ";
                        }
                        else
                        {
                            board.FormatFile(boardsize, filename, boardd);
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