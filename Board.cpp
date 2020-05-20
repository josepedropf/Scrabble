#include "Board.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

bool Board::IsLetter(char ch)
{
    for (int i = 0; i < lower_letters.size(); i++)
    {
        if (ch == lower_letters[i] || ch == upper_letters[i] || ch == '\'')
            return true;
    }
    return false;
}

void Board::Lowerstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = tolower(int(astring[i]));
    }
}

void Board::Upperstr(string &astring)
{
    for (int i=0; i < astring.size(); i++)
    {
        astring[i] = toupper(int(astring[i]));
    }
}

void Board::Letter_to_Int_Pos(vector <int> &numberpos, string normalpos)
{
    string lowerpos = normalpos;
    for (int i=0; i < normalpos.size(); i++)
    {
        lowerpos[i] = tolower(int(normalpos[i]));
    }

    for (int a=0; a < lowerpos.size(); a++)
    {
        for (int b=0; b < lower_letters.size(); b++)
        {
            if (lowerpos[a] == lower_letters[b])
            {
                numberpos[a] = b;
            }
        }
    }
}

bool Board::ValidPos(vector <int> numberpos, int bsize, vector <vector<char>> gameboard)
{
    return numberpos[0] < bsize && numberpos[1] < bsize && gameboard[numberpos[0]][numberpos[1]] != '1'
           && gameboard[numberpos[0]][numberpos[1]] != '2' && gameboard[numberpos[0]][numberpos[1]] != '3';
}

bool Board::EmptySpot(vector <vector<char>> gameboard, int boardsize)
{
    for (int i = 0; i < boardsize; i++)
    {
        for (int a = 0; a < boardsize; a++)
        {
            if (gameboard[i][a] == '0' || gameboard[i][a] == '4' || gameboard[i][a] == '5')
                return true;
            else if (i < boardsize - 1 && a < boardsize - 1 && (IsLetter(gameboard[i][a]) &&
                                                                (gameboard[i + 1][a] == '0' || gameboard[i + 1][a] == '3' || gameboard[i + 1][a] == '5') ||
                                                                (gameboard[i][a + 1] == '0' || gameboard[i][a + 1] == '2' || gameboard[i][a + 1] == '4')))
                return true;
        }
    }
    return false;
}

void Board::PickSize(int &boardsize)
{
    int decision = 0;
    cout << "Select the board size [4 to 20] (Length of the size of the square) or input 0 for a random size: ";
    while(1)
    {
        cin >> decision;
        if (cin.fail() || (decision < 4 && decision != 0) || decision > 20)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
            cout << "Select the board size [4 to 20] (Length of the size of the square) or input 0 for a random size: ";
        }
        else
            break;
    }

    if (decision == 0)
    {
        srand(time(0));
        boardsize = rand() % 17 + 4;
        cout << endl << "Board Size: " << boardsize << endl;
    }
    else
    {
        boardsize = decision;
    }
}

bool Board::ValidOrientation(vector <int> numberpos, int norient, int boardsize, vector <vector<char>> gameboard)
{
    if (MaxRange(numberpos, norient, boardsize, gameboard) < 2)
        return false;
    if (norient == 0)
    {
        if (numberpos[0] == boardsize - 1)
            return false;
        if (gameboard[numberpos[0]][numberpos[1]] == '4')
            return false;
        if (IsLetter(gameboard[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[0] == boardsize - 1 || IsLetter(gameboard[numberpos[0] + 1][numberpos[1]]) ||
                gameboard[numberpos[0] + 1][numberpos[1]] == '1' ||
                gameboard[numberpos[0] + 1][numberpos[1]] == '2' || gameboard[numberpos[0] + 1][numberpos[1]] == '4')
                return false;
        }
        return true;
    }
    else
    {
        if (numberpos[1] == boardsize - 1)
            return false;
        if (gameboard[numberpos[0]][numberpos[1]] == '5')
            return false;
        if (IsLetter(gameboard[numberpos[0]][numberpos[1]]))
        {
            if (numberpos[1] == boardsize - 1 || IsLetter(gameboard[numberpos[0]][numberpos[1] + 1]) ||
                gameboard[numberpos[0]][numberpos[1] + 1] == '1' ||
                gameboard[numberpos[0]][numberpos[1] + 1] == '3' || gameboard[numberpos[0]][numberpos[1] + 1] == '5')
                return false;
        }
        return true;
    }
}

bool Board::ValidWord(vector <int> numberpos, int orient, int boardsize, vector <vector<char>> gameboard,
                      string chosenword)
{
    //cout << endl << "VW" << endl;
    //cout << chosenword << endl;
    Upperstr(chosenword);
    if (gameboard[numberpos[0]][numberpos[1]] == '2' || gameboard[numberpos[0]][numberpos[1]] == '3')
    {
        //cout << endl << "CC" << endl;
        return false;
    }
    for (int i = 0; i < chosenword.size(); i++)
    {
        switch (orient)
        {
            case 0:
            {
                if (gameboard[numberpos[0] + i][numberpos[1]] != '0' && gameboard[numberpos[0] + i][numberpos[1]] != '3'
                    && gameboard[numberpos[0] + i][numberpos[1]] != '5')
                {
                    if (chosenword[i] != gameboard[numberpos[0] + i][numberpos[1]])
                    {
                        //cout << endl << "C0.1" << endl;
                        return false;
                    }
                }
                if (numberpos[0] + chosenword.size() < boardsize)
                {
                    if (IsLetter(gameboard[numberpos[0] + chosenword.size()][numberpos[1]]))
                    {
                        //cout << endl << "C0.2" << endl;
                        return false;
                    }
                }
                break;
            }
            case 1:
            {
                if (gameboard[numberpos[0]][numberpos[1] + i] != '0' && gameboard[numberpos[0]][numberpos[1] + i] != '2'
                    && gameboard[numberpos[0]][numberpos[1] + i] != '4')
                {
                    if (chosenword[i] != gameboard[numberpos[0]][numberpos[1] + i])
                    {
                        //cout << endl << "C1.1" << endl;
                        return false;
                    }
                }
                if (numberpos[1] + chosenword.size() < boardsize)
                {
                    if (IsLetter(gameboard[numberpos[0]][numberpos[1] + chosenword.size()]))
                    {
                        //cout << endl << "C1.2" << endl;
                        return false;
                    }
                }
                break;
            }
        }
    }
    return true;
}

int Board::MaxRange(vector<int> numberpos, int orient, int boardsize, vector<vector<char> > gameboard)
{
    int maxrange = boardsize - numberpos[orient];
    if (orient == 0)
    {
        for (int a = 0; a < boardsize - numberpos[0]; a++)
        {
            if (a < maxrange && (gameboard[numberpos[0] + a][numberpos[1]] == '1'
                                 || gameboard[numberpos[0] + a][numberpos[1]] == '2' ||
                                 gameboard[numberpos[0] + a][numberpos[1]] == '4'))
            {
                maxrange = a;
            }
        }
    }
    if (orient == 1)
    {
        for (int b = 0; b < boardsize - numberpos[1]; b++)
        {
            if (b < maxrange && (gameboard[numberpos[0]][numberpos[1] + b] == '1'
                                 || gameboard[numberpos[0]][numberpos[1] + b] == '3' ||
                                 gameboard[numberpos[0]][numberpos[1] + b] == '5'))
            {
                maxrange = b;
            }
        }
    }
    //cout << endl << "Max Range: " << maxrange << endl;
    return maxrange;
}

vector <string> Board::MatchingWords(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                                     vector <vector<char>> gameboard)
{
    //cout << endl << "MW" << endl;
    vector <string> matchwords;
    int maxrange = MaxRange(numberpos, orient, boardsize, gameboard);
    bool match = true;
    vector <char> criteria;
    if (maxrange > 1)
    {
        switch (orient)
        {
            case 0:
            {
                for (int a = 0; a < maxrange; a++)
                {
                    if (IsLetter(gameboard[numberpos[0] + a][numberpos[1]]))
                        criteria.push_back(gameboard[numberpos[0] + a][numberpos[1]]);
                    else
                        criteria.push_back('0');
                }
                break;
            }
            case 1:
            {
                for (int b = 0; b < maxrange; b++)
                {
                    if (IsLetter(gameboard[numberpos[0]][numberpos[1] + b]))
                        criteria.push_back(gameboard[numberpos[0]][numberpos[1] + b]);
                    else
                        criteria.push_back('0');
                }
                break;
            }
        }

        //cout << endl << "Criteria:  ";
        for (int c = 0; c < criteria.size(); c++)
        {
            //cout << criteria[c] << " ";
        }

        for (auto & possible_word : possible_words)
        {
            match = true;
            if (possible_word.size() <= maxrange)
            {
                if (possible_word.size() < criteria.size() && IsLetter(criteria[possible_word.size()]))
                    match = false;
                else
                {
                    for (int i = 0; i < possible_word.size(); i++)
                    {
                        if (criteria[i] != '0' && possible_word[i] != tolower(criteria[i]))
                            match = false;
                    }
                }
                if (match)
                    matchwords.push_back(possible_word);
            }
        }
    }
    return matchwords;
}

bool Board::AtLeastOneWord(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                           vector <vector<char>> gameboard)
{
    //cout << endl << "ALOW" << endl;
    vector <string> worange;
    worange = MatchingWords(numberpos, orient, boardsize, possible_words, gameboard);
    if (worange.size() == 0)
        return false;
    else
    {
        for (auto & i : worange)
        {
            if (ValidWord(numberpos, orient, boardsize, gameboard, i))
                return true;
        }
    }
    return false;
}

string Board::GetRandomWord(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                            vector <vector<char>> &gameboard)
{
    int word_index = 0, objpos = 0, wordpos = 0, maxrange;
    char obj;
    string chword;
    vector<string> matchingw;
    matchingw = MatchingWords(numberpos, orient, boardsize, possible_words, gameboard);
    //cout << endl << "GRW" << endl;
    int mwsize = 0, section = 0;
    //cout << endl << "Matching Words Size: " << matchingw.size() << endl;
    while (true)
    {
        srand(time(0));
        mwsize = matchingw.size();
        word_index = rand() % mwsize;
        chword = matchingw[word_index];

        if (ValidWord(numberpos, orient, boardsize, gameboard, chword))
            break;
        else
            matchingw.erase(matchingw.begin() + word_index);
    }
    //cout << "Selected Word: " << chword << endl;
    return chword;
}

void Board::WordPlacer(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                       vector <vector<char>> &gameboard, string chword)
{
    //cout << endl << "WP" << endl;
    Upperstr(chword);
    if (orient == 0)
        chorient.push_back('V');
    if (orient == 1)
        chorient.push_back('H');
    string position = "Aa";
    position[0] = upper_letters[numberpos[0]];
    position[1] = lower_letters[numberpos[1]];
    strcoord.push_back(position);
    Upperstr(chword);
    wordlist.push_back(chword);

    for (int i = 0; i < chword.size(); i++)
    {
        switch (orient)
        {
            case 0:
            {
                gameboard[numberpos[0] + i][numberpos[1]] = chword[i];
                break;
            }
            case 1:
            {
                gameboard[numberpos[0]][numberpos[1] + i] = chword[i];
                break;
            }
        }
    }
    switch (orient)
    {
        case 0:
        {
            if (numberpos[0] > 0)
            {
                gameboard[numberpos[0] - 1][numberpos[1]] = '1';
            }
            if (numberpos[0] + chword.size() < boardsize)
            {
                gameboard[numberpos[0] + chword.size()][numberpos[1]] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[1] < boardsize - 1 && !IsLetter(gameboard[numberpos[0] + i][numberpos[1] + 1]))
                {
                    if (gameboard[numberpos[0] + i][numberpos[1] + 1] != '3'
                        && gameboard[numberpos[0] + i][numberpos[1] + 1] != '5' &&
                        gameboard[numberpos[0] + i][numberpos[1] + 1] != '1')
                        gameboard[numberpos[0] + i][numberpos[1] + 1] = '2';
                    else
                        gameboard[numberpos[0] + i][numberpos[1] + 1] = '1';
                }
                if (numberpos[1] > 0)
                {
                    if (gameboard[numberpos[0] + i][numberpos[1] - 1] == '0')
                        gameboard[numberpos[0] + i][numberpos[1] - 1] = '4';
                    else if (gameboard[numberpos[0] + i][numberpos[1] - 1] == '3'
                             || gameboard[numberpos[0] + i][numberpos[1] - 1] == '5')
                        gameboard[numberpos[0] + i][numberpos[1] - 1] = '1';
                }
            }
            break;
        }
        case 1:
        {
            if (numberpos[1] > 0)
            {
                gameboard[numberpos[0]][numberpos[1] - 1] = '1';
            }
            if (numberpos[1] + chword.size() < boardsize)
            {
                gameboard[numberpos[0]][numberpos[1] + chword.size()] = '1';
            }
            for (int i = 0; i < chword.size(); i++)
            {
                if (numberpos[0] < boardsize - 1 && !IsLetter(gameboard[numberpos[0] + 1][numberpos[1] + i]))
                {
                    if (gameboard[numberpos[0] + 1][numberpos[1] + i] != '2'
                        && gameboard[numberpos[0] + 1][numberpos[1] + i] != '4' &&
                        gameboard[numberpos[0] + 1][numberpos[1] + i] != '1')
                        gameboard[numberpos[0] + 1][numberpos[1] + i] = '3';
                    else
                        gameboard[numberpos[0] + 1][numberpos[1] + i] = '1';
                }
                if (numberpos[0] > 0)
                {
                    if (gameboard[numberpos[0] - 1][numberpos[1] + i] == '0')
                        gameboard[numberpos[0] - 1][numberpos[1] + i] = '5';
                    else if (gameboard[numberpos[0] - 1][numberpos[1] + i] == '2'
                             || gameboard[numberpos[0] - 1][numberpos[1] + i] == '4')
                        gameboard[numberpos[0] - 1][numberpos[1] + i] = '1';
                }
            }
            break;
        }
    }
}

void Board::RandomWordPlacement(vector <int> numberpos, int orient, int boardsize, vector <string> possible_words,
                                vector <vector<char>> &gameboard)
{
    string chosenw;
    chosenw = GetRandomWord(numberpos, orient, boardsize, possible_words, gameboard);
    string ori = "H";
    if (orient == 0)
        ori = "V";
    else
        ori ="H";
    //cout << endl << "Position: " << numberpos[0] << ", " << numberpos[1] << "   Orientation: " << ori;
    //cout << endl << "Chosen Word: " << chosenw << endl;
    WordPlacer(numberpos, orient, boardsize, possible_words, gameboard, chosenw);
}

void Board::PlayerWord(vector <int> numberpos, int orient, int boardsize,vector <string> possible_words,
                       vector <vector<char>> &gameboard)
{
    string playerw, keepdec;
    vector <string> worange;
    cout << endl << "Please Introduce a Word (maximum number of letters: " <<
         MaxRange(numberpos, orient, boardsize, gameboard) << ") -> " ;
    while(1)
    {
        cin >> playerw;
        if (cin.fail() || playerw.size() < 2
            || playerw.size() > MaxRange(numberpos, orient, boardsize, gameboard)
            || !ValidWord(numberpos, orient, boardsize, gameboard, playerw))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid Word" << endl;
            cout << "Do you want to keep the same coordinates and orientation ? [Y for yes || N for no] ";
            while(1)
            {
                cin >> keepdec;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Invalid Input!" << endl;
                    cout << "Do you want to keep the same coordinates and orientation ? [Y for yes || N for no] ";
                }
                else
                    break;
            }
            Lowerstr(keepdec);
            if (keepdec == "n")
            {
                break;
            }
            else
            {
                cout << endl << "Please Introduce a Word (maximum number of letters: " <<
                     MaxRange(numberpos, orient, boardsize, gameboard) << ") -> " ;
            }
        }
        else
        {
            WordPlacer(numberpos, orient, boardsize, possible_words, gameboard, playerw);
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }


}

void Board::Coordinates(vector <vector<char>> &gameboard,
                        int boardsize, vector <int> npos, vector <string> possible_words, int mode)
{
    pos = " ";
    while (pos != "end" || (pos == "end" && empty_board))
    {
        DrawBoardClean(boardsize, gameboard);
        cout << endl << endl << endl;
        // DrawBoard(boardsize, gameboard);
        cout << endl << "Coordinates must be indicated as two letters having in base the board above." << endl;
        cout << "Introduce the coordinates of the first letter of the word "
                "(or end if you don't want to add more words to the board): ";
        while(1)
        {
            cin >> pos;
            if (pos == "end" && !empty_board)
                break;
            if (cin.fail() || pos.size() != 2 || (pos == "end" && empty_board))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                if (pos == "end" && empty_board)
                    cout << endl << "You can't leave the board empty!";
                cout << endl << "Coordinates must be indicated as two letters having in base the board above." << endl;
                cout << "Introduce the coordinates of the first letter of the word "
                        "(or end if you don't want to add more words to the board): ";
            }
            else
            {
                Letter_to_Int_Pos(npos, pos);
                if (!ValidPos(npos, boardsize, gameboard))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Coordinates must be indicated as two letters having in base the board above."
                         << endl;
                    cout << "Introduce the coordinates of the first letter of the word "
                            "(or end if you don't want to add more words to the board): ";
                }
                else
                {
                    empty_board = false;
                    break;
                }
            }
        }
        if (pos != "end")
        {
            cout << endl << "Valid Position!" << endl;
            cout << "Introduce the word orientation (H for Horizontal || V for Vertical): ";
            while(1)
            {
                cin >> orientation;
                if (cin.fail() || (orientation != lower_letters[7] && orientation != lower_letters[21]
                                   && orientation != upper_letters[7] && orientation != upper_letters[21]))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Introduce the word orientation (H for Horizontal || V fo Vertical): ";
                }
                else
                {
                    if (orientation == 'h' || orientation == 'H')
                        numborient = 1;
                    else
                        numborient = 0;

                    if (!ValidOrientation(npos, numborient, boardsize, gameboard))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << endl << "The orientation is Invalid for the position you chose previously!" << endl;
                        break;
                    }
                    else if (mode != 3 && !AtLeastOneWord(npos, numborient, boardsize, possible_words, gameboard))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << endl << "There is no Valid Word for that combination of coordinates and orientation!"
                             << endl;
                        break;
                    }
                    else
                    {
                        if (mode == 1)
                        {
                            RandomWordPlacement(npos, numborient, boardsize, possible_words, gameboard);
                            break;
                        }
                        if (mode == 3)
                        {
                            PlayerWord(npos, numborient, boardsize, possible_words, gameboard);
                            break;
                        }
                    }
                }
            }
        }
    }
    cout << endl << "Board Done" << endl;
}



void Board::GetWords(vector <string> &possible_words, vector <vector<char>> gameboard)
{
    fstream wordfile;
    wordfile.open("WORDS.TXT");
    string content;

    while(getline(wordfile, content))
    {
        if (content.size() > 1)
            possible_words.push_back(content);
        //cout << content << endl;
    }
    possible_words.erase(possible_words.begin());
    wordfile.close();
}

void Board::DrawBoard(int boardsize, vector <vector<char>> gameboard)
{
    cout << "   ";
    for (int i = 0; i < boardsize; i++)
        cout << lower_letters[i] << "  ";
    cout << endl;
    for (int a = 0; a < boardsize; a++)
    {
        cout << upper_letters[a] << "  ";
        for (int b = 0; b < boardsize; b++)
        {
            cout << gameboard[a][b] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::DrawBoardClean(int boardsize,  vector <vector<char>> gameboard)
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
            if (IsLetter(gameboard[a][b]))
                drawch = gameboard[a][b];
            cout << drawch << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Board::RandomBoard(int boardsize, vector <int> npos, vector <vector<char>> &gameboard, vector <string> possible_words)
{
    int nwords = 4;
    cout << "Select the number of words [4 to " << (4 * boardsize) + 4 << "] or input 0 for a random number: ";
    while(1)
    {
        cin >> nwords;
        if (cin.fail() || (nwords < 4 && nwords != 0) || nwords > (4 * boardsize) + 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
            cout << "Select the number of words [4 to " << (4 * boardsize) + 4 << "] or input 0 for a random number: ";
        }
        else
            break;
    }

    if (nwords == 0)
    {
        srand(time(0));
        nwords = rand() % (4 * boardsize) + 4;
        cout << endl << "Number of Words: " << nwords << endl;
    }

    vector <vector<int>> allpos;
    vector <int> vpos;
    for (int a = 0; a < boardsize; a++)
    {
        for (int b = 0; b < boardsize; b++)
        {
            vpos.clear();
            vpos = {a, b};
            allpos.push_back(vpos);
        }
    }
    bool validword = false;
    int randpos = 0, randomor = 0, line = 0, col = 0;
    for (int i = 0; i < nwords; i++)
    {
        if (allpos.size() == 1 || !EmptySpot(gameboard, boardsize) || i == nwords)
            break;
        validword = false;
        while (!validword)
        {
            if (allpos.size() > 1)
            {
                srand(time(0));
                randpos = rand() % allpos.size();
                line = allpos[randpos][0];
                col = allpos[randpos][1];
                npos = {line, col};
            }
            if (!ValidPos(npos, boardsize, gameboard) ||
                ((!AtLeastOneWord(npos, 0, boardsize, possible_words, gameboard) || !ValidOrientation(npos, 0, boardsize, gameboard)) &&
                 (!AtLeastOneWord(npos, 1, boardsize, possible_words, gameboard) || !ValidOrientation(npos, 1, boardsize, gameboard))))
            {
                //cout << endl << "Eliminated: " << allpos[randpos][0] << ", " << allpos[randpos][1] << endl;
                allpos.erase(allpos.begin() + randpos);
            }
            else
            {
                srand(time(0));
                randomor = rand() % 2;
                if (AtLeastOneWord(npos, randomor, boardsize, possible_words, gameboard) && ValidOrientation(npos, randomor, boardsize, gameboard))
                {
                    //cout << endl << "TestPosition: " << allpos[randpos][0] << ", " << allpos[randpos][1] << "   TestOri: " << randomor <<endl;
                    RandomWordPlacement(npos, randomor, boardsize, possible_words, gameboard);
                    validword = true;
                }
                if (!validword)
                {
                    if (randomor == 0)
                        randomor = 1;
                    else
                        randomor = 0;
                    if (AtLeastOneWord(npos, randomor, boardsize, possible_words, gameboard) && ValidOrientation(npos, randomor, boardsize, gameboard))
                    {
                        //cout << endl << "TestPosition: " << allpos[randpos][0] << ", " << allpos[randpos][1] << "   TestOri: " << randomor <<endl;
                        RandomWordPlacement(npos, randomor, boardsize, possible_words, gameboard);
                        validword = true;
                    }
                }
            }
        }
        DrawBoardClean(boardsize, gameboard);
        // DrawBoard(boardsize, gameboard);
    }
    DrawBoardClean(boardsize, gameboard);
}

void Board::FormatFile(int boardsize, string filename, vector<vector<char>> gameboard)
{
    string boardfilename = filename + ".txt";
    ofstream boardfile(boardfilename);
    boardfile << boardsize << " x " << boardsize << endl;
    cout << gameboard.size();
    for (int i = 0; i < chorient.size(); i++)
    {
        boardfile << strcoord[i] << " " << chorient[i] << " " << wordlist[i] << endl;
    }

    char drawch = ' ';
    boardfile << endl << "   ";
    for (int i = 0; i < boardsize; i++)
        boardfile << lower_letters[i] << "  ";
    boardfile << endl;
    for (int a = 0; a < boardsize; a++)
    {
        boardfile << upper_letters[a] << "  ";
        for (int b = 0; b < boardsize; b++)
        {
            drawch = ' ';
            if (IsLetter(gameboard[a][b]))
                drawch = gameboard[a][b];
            boardfile << drawch << "  ";
        }
        boardfile << endl;
    }
    boardfile << endl << endl;
    boardfile.close();
}
