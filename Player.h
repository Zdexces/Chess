#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player{
public:
    std::string name;
    bool side = 0, turn = 0; //0 - black(not your turn), 1 - white(your turn)
    Player(){};
    Player(bool);
    ~Player(){}
};

#endif