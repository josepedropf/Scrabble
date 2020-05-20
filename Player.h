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
    vector <int> fscorep1, fscorep2, fscorep3, fscorep4;
    bool ia1 = false, ia2 = false, ia3 = false, ia4 = false;
    int scorep1 = 0, scorep2 = 0, scorep3 = 0, scorep4 = 0;

    void GetPlayers();
    // Asks the Number of Players and implements said number
    void CustomPlayerNames();
    // Asks if the user wants to customize the name of each player and in case he wants
    // asks the what name to give each player depending on the number of players
    void GetIA();
    // Asks how many IA Players the user wants. Presents a list of integers for each possible combination of IA Players and Normal ones 

};


#endif //SCRABBLEJUNIOR_PLAYER_H
