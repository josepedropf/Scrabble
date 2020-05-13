#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_POOL_H
#define SCRABBLEJUNIOR_POOL_H
using namespace std;

class Pool {
public:
    vector <char> pool;
    vector <char> charp1;
    vector <char> charp2;
    vector <char> charp3;
    vector <char> charp4;

    void InitialPool(vector<vector <char>> gameboard, int boardsize);
    // Gets the characters from the Game Board in order to make the initial letter pool
    char DrawRandomChar();
    void InitialDraw(int ndraw, int np);
    void WritePlrPool(vector <char> plrpool, string pname);
    void DrawPoolTurn(vector <char> &plrpool, int drawcount);
};


#endif //SCRABBLEJUNIOR_POOL_H
