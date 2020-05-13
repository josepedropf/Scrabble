#include <string>
#include <vector>
#ifndef SCRABBLEJUNIOR_PLAYER_H
#define SCRABBLEJUNIOR_PLAYER_H
using namespace std;

class Player {
public:
    int nplayers;
    string pname1 = "Player 1";
    string pname2 = "Player 2";
    string pname3 = "Player 3";
    string pname4 = "Player 4";
    int scorep1 = 0, scorep2 = 0, scorep3 = 0, scorep4 = 0;

    void GetPlayers();
    void CustomPlayerNames();

private:

};


#endif //SCRABBLEJUNIOR_PLAYER_H
