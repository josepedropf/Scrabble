#include "Pool.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

void SetColor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

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
    cout << "Letters in play: \n";
    SetColor(2);
    for (char b : pool)
    {
        cout << endl << b;
    }
    SetColor(1);
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

void Pool::WritePlrPool(vector<char> plrpool, string pname)
{
    int poolsize = plrpool.size();
    cout << endl << "Current " << pname << "'s Pool: ";
    for (int i = 0; i < poolsize; i++)
    {
        cout << plrpool[i] << "  ";
    }
    cout << endl;
}

void Pool::DrawPoolTurn(vector<char> &plrpool, int drawcount)
{
    cout << endl << "Pool Tiles Retrieved: ";
    for (int i = 0; i < drawcount; i++)
    {
        char dchar = DrawRandomChar();
        plrpool.push_back(dchar);
        cout << dchar << "  ";
    }
    cout << endl;
}

void Pool::ExchangeTiles(vector<char> &plrpool)
{
    int tiles = 2, plrpoolindex = 0;
    if (pool.size() == 1)
        tiles = 1;
    else
        tiles = 2;
    for (int i = 0; i < tiles; i++)
    {
        srand(time(0));
        plrpoolindex = rand() % plrpool.size();
        pool.push_back(plrpool[plrpoolindex]);
        plrpool.erase(plrpool.begin() + plrpoolindex);
    }
    DrawPoolTurn(plrpool, tiles);
}
