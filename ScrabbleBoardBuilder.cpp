#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

int boardsize = 1;
vector <string> possible_words;
vector <char> lower_letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector <char> upper_letters;

int main()
{
    cout << "Select the board size (Length of the size of the square): ";
    while(1)
    {
        cin >> boardsize;
        if (cin.fail() || boardsize < 1 || boardsize > 20)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid board size (Input a number between 1 and 20)" << endl;
            cout << "Select the board size (Length of the size of the square): ";
        }
        else
            break;
    }
    
    fstream wordfile;
    //wordfile.open("C:\\Users\\MSI\\Desktop\\WORDS.TXT");
    wordfile.open("WORDS.TXT");
    string content;

    while(getline(wordfile, content))
    {
        possible_words.push_back(content);
        //cout << content << endl;
    }
    wordfile.close();
    
    for (int i = 0; i < size(lower_letters); i++)
        upper_letters.push_back(toupper(lower_letters[i]));
    
    cout << " ";
    for (int i = 0; i < boardsize; i++)         // output lower letters column
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int i = 0; i < boardsize; i++)         // output upper letters column
        cout << upper_letters[i] << endl;
    
    string pos;
}
