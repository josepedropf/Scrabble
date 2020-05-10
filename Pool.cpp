#include "Pool.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

void Pool::InitialPool(vector<vector <char>> gameboard, int boardsize)
{
    for (int i = 0; i < boardsize; i++)
    {
        for (int a = 0; a < boardsize; a++)
        {
            if (gameboard[i][a] != '0')
                pool.push_back(gameboard[i][a]);
        }
    }
    for (int b = 0; b < pool.size(); b++)
    {
        cout << endl << pool[b];
    }
    cout << endl;
}
