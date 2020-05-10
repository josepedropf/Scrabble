#include "ScrabbleBoard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

void ScrabbleBoard::OpenBoard(string filename)
{
    gameboard.clear();
    vector <int> linepos;
    vector <int> colpos;
    vector <int> orient;
    vector <char> boardline;
    vector <string> words;
    string word = "";
    ifstream boardfile;
    string path = "C:\\Users\\MSI\\CLionProjects\\ScrabbleBoardBuilder\\cmake-build-debug\\";
    string txtfilename = path + filename + ".txt";
    boardfile.open(txtfilename);
    string line;
    getline(boardfile, line);
    if (line[1] == 'x')
        boardsize = line[0];
    else
    {
        string bs = line.substr(0, 2);
        boardsize = stoi(bs);
    }
    while (true)
    {
        getline(boardfile, line);
        if (line.size() == 0)
            break;
        else
        {
            for (int i = 0; i < lower_letters.size(); i++)
            {
                if (lower_letters[i] == line[1])
                    colpos.push_back(i);
                if (upper_letters[i] == line[0])
                    linepos.push_back(i);
            }
            if (line[3] == 'H')
                orient.push_back(1);
            else
                orient.push_back(0);
            word = "";
            for (int i = 5; i < line.size(); i++)
            {
                word.push_back(line[i]);
            }
            words.push_back(word);
        }
    }
    for (int i = 0; i < boardsize; i++)
    {
        boardline.push_back('0');
    }

    for (int i = 0; i < boardsize; i++)
    {
        gameboard.push_back(boardline);
    }

    for (int i = 0; i < linepos.size(); i++)
    {
        string wrd = words[i];
        for (int a = 0; a < wrd.size(); a++)
        {
            switch (orient[i])
            {
                case 0:
                    {
                    gameboard[linepos[i] + a][colpos[i]] = wrd[a];
                    break;
                }
                case 1:
                    {
                    gameboard[linepos[i]][colpos[i] + a] = wrd[a];
                    break;
                }
            }
        }
    }
    boardfile.close();
}

void ScrabbleBoard::DrawGameBoard()
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
            if (isalpha(gameboard[a][b]))
                drawch = gameboard[a][b];
            cout << drawch << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
}
