#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

void Player::GetPlayers()
{
    while(true)
    {
        cout << "What will be the number of players? [2-4]: ";
        cin >> nplayers;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input!" << endl;
        }
        else if (nplayers > 4 || nplayers < 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "The number has to be in the range [2-4]!" << endl;
        }
        else
            break;
    }
}

void Player::CustomPlayerNames()
{
    int pcount = 1;
    for (pcount; pcount <= nplayers; pcount++)
    {
        while (true)
        {
            cout << endl << "Player " << to_string(pcount) << " Introduce your Custom Name: ";
            switch (pcount)
            {
                case 1:
                {
                    cin >> pname1;
                    break;
                }
                case 2:
                {
                    cin >> pname2;
                    break;
                }
                case 3:
                {
                    cin >> pname3;
                    break;
                }
                case 4:
                {
                    cin >> pname4;
                    break;
                }
            }
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << endl << "Invalid input!" << endl;
            }
            else
                break;
        }
    }
}

void Player::GetIA()
{
    int iaanswer = 0;

    switch (nplayers)
    {
        case 2:
        {
            while (true)
            {
                cout << endl << "Input 0 for no IA Players" << endl;
                cout << "Input 1 for 1 Normal vs 1 IA" << endl;
                cout << "Input 2 for 2 IA Players" << endl;
                cin >> iaanswer;
                if (cin.fail() || iaanswer < 0 || iaanswer > 2)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Invalid input!" << endl;
                }
                else
                    break;
            }
            break;
        }
        case 3:
        {
            while (true)
            {
                cout << endl << "Input 0 for no IA Players" << endl;
                cout << "Input 3 for 2 Normal vs 1 IA" << endl;
                cout << "Input 4 for 1 Normal vs 2 IA" << endl;
                cout << "Input 5 for 3 IA Players" << endl;
                cin >> iaanswer;
                if (cin.fail() || iaanswer < 0 || iaanswer > 5 || iaanswer == 2 || iaanswer == 3)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Invalid input!" << endl;
                }
                else
                    break;
            }
            break;
        }
        case 4:
        {
            while (true)
            {
                cout << endl << "Input 0 for no IA Players" << endl;
                cout << "Input 6 for 3 Normal vs 1 IA" << endl;
                cout << "Input 7 for 2 Normal vs 2 IA" << endl;
                cout << "Input 8 for 1 Normal vs 3 IA" << endl;
                cout << "Input 9 for 4 IA Players" << endl;
                cin >> iaanswer;
                if (cin.fail() || (iaanswer < 6 && iaanswer != 0) || iaanswer > 9)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << "Invalid input!" << endl;
                }
                else
                    break;
            }
            break;
        }
    }
    switch (iaanswer)
    {
        case 0:
            break;
        case 1:
        {
            ia2 = true;
            break;
        }
        case 2:
        {
            ia1 = true;
            ia2 = true;
            break;
        }
        case 3:
        {
            ia3 = true;
            break;
        }
        case 4:
        {
            ia2 = true;
            ia3 = true;
            break;
        }
        case 5:
        {
            ia1 = true;
            ia2 = true;
            ia3 = true;
            break;
        }
        case 6:
        {
            ia4 = true;
            break;
        }
        case 7:
        {
            ia3 = true;
            ia4  = true;
            break;
        }
        case 8:
        {
            ia2 = true;
            ia3 = true;
            ia4 = true;
            break;
        }
        case 9:
        {
            ia1 = true;
            ia2 = true;
            ia3 = true;
            ia4 = true;
            break;
        }
    }
}
