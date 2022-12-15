#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>


using std::string;
using std::exception;
using std::cerr;
using std::endl;

class IllegalInput : public exception{
private:
    string _e_msg = "Unexpected input. Try again, Human.";
    int _code = 100;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class TargetingEmptyPosition : public exception{
private:
    string _e_msg = "There's nothing there, Human. Try again.";
    int _code = 101;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class TargetingEnemyPiece : public exception{
private:
    string _e_msg = "Those are not yours to command, Human. Try again.";
    int _code = 102;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class IllegalMove: public exception{
private:
    string _e_msg = "Illegal move detected. Try again, Human.";
    int _code = 103;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class ObstructedPath : public exception{
private:
    string _e_msg = "The path for this piece is obstructed. Try again, Human.";
    int _code = 104;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class SandbagMove : public exception{
private:
    string _e_msg = "Human, those are your own pieces. Try again.";
    int _code = 105;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class CheckBlockingPieceMove : public exception{
private:
    string _e_msg = "This piece is blocking enemy check, Human. Try again.";
    int _code = 106;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};

class OutOfBoundsCoordinates : public exception{
private:
    string _e_msg = "Your input was out of the board boundaries. Try again, Human.";
    int _code = 107;
public:
    void what(){
        cerr << "Error code: " << _code << ".\nError description: " << _e_msg << endl << endl;
    }    
};



#endif