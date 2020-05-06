#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_POOL_H
#define SCRABBLEJUNIOR_POOL_H
using namespace std;

class Pool {
public:
    vector <char> pool;
    void InitialPool(vector<vector <char>> gameboard, int boardsize, vector <char> &pool);
    // Gets the characters from the Game Board in order to make the initial letter pool
};


#endif //SCRABBLEJUNIOR_POOL_H
