#include "Player.h"

using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

Player::Player(bool s){
    cout << "Please provide your Name, Human." << endl;
    getline(cin, name);
    cout << "Accepted." << endl;
    side = s;
    if(side){ //whites go first
        turn = 1;
    }
    else{
        turn = 0;
    }
}
