#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_POOL_H
#define SCRABBLEJUNIOR_POOL_H
using namespace std;

class Pool {
public:
    vector <char> pool, charp1, charp2, charp3, charp4;

    void InitialPool(vector<vector <char>> gameboard, int boardsize, unsigned int color1, unsigned int color2);
    // Gets the characters from the Game Board in order to make the initial letter Pool
    char DrawRandomChar();
    // Gets a Random Character out of the Main Pool, erasing it from said Pool
    void InitialDraw(int ndraw, int np);
    // Distributes 7 tiles per player in the beggining of each game,
    // or the maximum of tiles possible per player if there aren't enough for 7 per player at the start
    void WritePlrPool(vector<char> plrpool, string pname, unsigned int color1, unsigned int color2);
    // Writes the charaters in the Pool of the specified player, next to it's name and with the chosen colors
    void DrawPoolTurn(vector <char> &plrpool, int drawcount);
    // Draws one or two tiles from the Main Pool depending on how many tiles the player used during his turn
    void ExchangeTiles(vector <char> &plrpool);
    // In the case of not being able to play, the player excahnges tiles with the Main Pool
    // This function not only draws Random Characters from the Main Pool but also puts tiles in the Main Pool from the Player's Pool
};


#endif //SCRABBLEJUNIOR_POOL_H
