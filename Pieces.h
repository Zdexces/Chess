#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include "Exception.h"

const int BOARD_COORD_MIN = 1;
const int BOARD_COORD_MAX = 8;

class Piece{
public:
    Piece(){}
    Piece(int, int, bool); // default constructor
    std::pair <int, int> x_y = {0, 0};
    bool side = 0; //false = black, true = white
    bool is_alive = 1;
    int type = 0;
    virtual std::vector <std::pair <int, int>> getPossibleMoves() = 0;
    void moveCross(std::vector<std::pair<int, int>>&, std::pair <int, int>);
    void moveDiag(std::vector<std::pair<int, int>>&, std::pair <int, int>);
    bool checkNotOutOfBound(std::pair <int, int>);
    virtual void move(int, int);
    virtual ~Piece(){};
};

class King : public Piece{ //cannot come close to a King!
public:
    King(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
};

class Queen : public Piece{
public:
    Queen(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
};

class Rook : public Piece{
public:
    Rook(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
};

class Bishop : public Piece{
public:
    Bishop(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
};

class Knight : public Piece{
public:
    Knight(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
};

class Pawn : public Piece{
public:
    Pawn(int, int, bool);
    using Piece :: Piece;
    virtual std::vector <std::pair <int,int>> getPossibleMoves();
    //Queen transform();
};



#endif