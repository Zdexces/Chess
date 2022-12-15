#include "Pieces.h"


using std::vector;
using std::pair;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;


Piece::Piece(int x, int y, bool s){
    x_y = {x, y};
    side = s;
}

void Piece::move(int x, int y){
    pair <int, int> p = {x, y};
    vector <pair <int, int>> v = getPossibleMoves();
    if(std::find(v.begin(), v.end(), p) != v.end()){
        x_y = p;
    }
    else{
        throw IllegalMove(); //replace with throw
    }
}

void Piece::moveCross(vector <pair <int, int>>& m, pair <int, int> xy){
    for(int y = BOARD_COORD_MIN; y <= BOARD_COORD_MAX; y++){
        if(y != xy.second){
            m.push_back({xy.first, y});
        }
    }
    for(int x = BOARD_COORD_MIN; x <= BOARD_COORD_MAX; x++){
        if(x != xy.first){
            m.push_back({x, xy.second});
        }
    }
}

void Piece::moveDiag(vector <pair <int, int>>& m, pair <int, int> xy){
    for(int x = BOARD_COORD_MIN; x <= BOARD_COORD_MAX; x++){
        for(int y = BOARD_COORD_MIN; y <= BOARD_COORD_MAX; y++){
            if(x + y == (xy.first + xy.second)){
                if(x != xy.first || y != xy.second){
                    m.push_back({x, y});
                }
            }
            if(x - y == (xy.first - xy.second)){
                if(x != xy.first || y != xy.second){
                    m.push_back({x, y});
                }
            }
        }
    }
}

bool Piece::checkNotOutOfBound(pair <int, int> xy){
    if(xy.first < (BOARD_COORD_MAX + 1) &&
        xy.first > (BOARD_COORD_MIN - 1) &&
        xy.second < (BOARD_COORD_MAX + 1) &&
        xy.second > (BOARD_COORD_MIN - 1)){
        return 1;
    }
    else{
        return 0;
    }
}

King::King(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 1;
}

vector <pair<int, int>> King::getPossibleMoves(){
    vector <pair<int, int>> moves;
    for(int y = x_y.second - 1; y < 3 + (x_y.second - 1); y++){
        for(int x = x_y.first - 1; x < 3 + (x_y.first - 1); x++){
            if(checkNotOutOfBound({x, y}) && (x != x_y.first || y != x_y.second)){
                moves.push_back({x, y});
            }
        }
    }
    return moves;
}


Queen::Queen(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 2;
}

vector <pair<int, int>> Queen::getPossibleMoves(){
    vector <pair<int, int>> moves;

    //cross movement:

    moveCross(moves, x_y);

    //diagonal movement:

    moveDiag(moves, x_y);

    return moves;
}


Rook::Rook(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 3;
}

vector <pair<int, int>> Rook::getPossibleMoves(){
    vector <pair<int, int>> moves;

    //cross movement only:
    moveCross(moves, x_y);
    return moves;
}


Bishop::Bishop(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 4;
}

vector <pair<int, int>> Bishop::getPossibleMoves(){
    vector <pair<int, int>> moves;

    //diagonal movement only:

    moveDiag(moves, x_y);
    return moves;
}


Knight::Knight(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 5;
}

vector <pair<int, int>> Knight::getPossibleMoves(){
    vector <pair<int, int>> moves, fill, sub;

    //~pepega~ knight-style movement = filler(5�5) a.k.a @see fill - queen's movement a.k.a @see sub:

    //sub initialisation:
    moveCross(sub, x_y);
    moveDiag(sub, x_y);
    //fill initialisation:
    for(int x = x_y.first - 2; x < (3 + x_y.first); x++){
        for(int y = x_y.second - 2; y < (3 + x_y.second); y++){
            if(checkNotOutOfBound({x, y}) && (x != x_y.first || y != x_y.second)){
                fill.push_back({x, y});
            }
        }
    }
    //substracting:
    for(int i = 0; i < fill.size(); i++){
        if(std::find(sub.begin(), sub.end(), fill[i]) == sub.end()){
            moves.push_back(fill[i]);
        }
    }

    return moves;
}


Pawn::Pawn(int x, int y, bool s){
    x_y = {x, y};
    side = s;
    type = 6;
}


vector <pair<int, int>> Pawn::getPossibleMoves(){
    vector <pair<int, int>> moves;
    if(side){    
        for(int y = x_y.second - 1; y < 2 + x_y.second; y++){
            if(checkNotOutOfBound({x_y.first, y}) && ((x_y.first - 1) >= BOARD_COORD_MIN)){
                moves.push_back({x_y.first - 1, y});
            }
        }
    }
    else{
        for(int y = x_y.second - 1; y < 2 + x_y.second; y++){
            if(checkNotOutOfBound({x_y.first, y}) && ((x_y.first + 1) <= BOARD_COORD_MAX)){
                moves.push_back({x_y.first + 1, y});
            }
        }
    }
    return moves;
}

