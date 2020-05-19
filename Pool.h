#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_POOL_H
#define SCRABBLEJUNIOR_POOL_H
using namespace std;

class Pool {
public:
    vector <char> pool, charp1, charp2, charp3, charp4;

    void InitialPool(vector<vector <char>> gameboard, int boardsize, unsigned int color1, unsigned int color2);
    // Gets the characters from the Game Board in order to make the initial letter pool
    char DrawRandomChar();
    void InitialDraw(int ndraw, int np);
    void WritePlrPool(vector<char> plrpool, string pname, unsigned int color1, unsigned int color2);
    void DrawPoolTurn(vector <char> &plrpool, int drawcount);
    void ExchangeTiles(vector <char> &plrpool);
};


#endif //SCRABBLEJUNIOR_POOL_H
