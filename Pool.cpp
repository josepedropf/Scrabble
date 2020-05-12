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

char Pool::DrawRandomChar()
{
    char pchar;
    srand(time(0));
    int poolindex = rand() % pool.size();
    pchar = pool[poolindex];
    pool.erase(pool.begin() + poolindex);
    return pchar;
}

void Pool::InitialDraw(int ndraw, int np)
{
    for (int i = 0; i < ndraw; i++)
    {
        charp1.push_back(DrawRandomChar());
        charp2.push_back(DrawRandomChar());
        if (np >= 3)
            charp3.push_back(DrawRandomChar());
        if (np == 4)
            charp4.push_back(DrawRandomChar());
    }
}
