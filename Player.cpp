#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
void Player::getPlayers() {
    while(true)
    {
        cout << "What will be the number of players? [2-4]";
        cin >> nplayers;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Invalid input!" << endl;
        }

        if (nplayers > 4 || nplayers < 2) {
            cout << endl << "Invalid input!" << endl;
        }

        else
            break;
    }


}
