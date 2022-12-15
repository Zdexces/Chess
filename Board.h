#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include "Exception.h"
#include "Player.h"
#include <map>

using std::vector;
using std::pair;
using std::string;
using std::map;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;


class Board{
public:
	vector <vector <char>> board;
	vector <Piece*> pieces;
	vector < vector <pair <int, int>>> pathing;
	map <int, char> type_to_disp = {{1, 'K'}, {2, 'Q'}, {3, 'R'}, {4, 'B'}, {5, 'k'}, {6, 'p'}};
	Board();
	void drawBoard();
	void clearBoard(bool);
	void clearError(bool);
	bool isTheCommandLegal(string);
	pair <int, int> transformXY(pair <char, int>);
	void spawnGame(Player&, Player&);
	int findPiece(pair <int, int>, bool);
	int findTarget(pair <int, int>, bool);
	bool checkCollision(pair <int, int>, pair <int, int>);
	~Board();
};

#endif
