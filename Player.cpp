#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
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

