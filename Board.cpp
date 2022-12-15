#include "Board.h"

using std::vector;
using std::pair;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::getline;

Board::Board(){

	//pieces init

	pieces.resize(32);
	pieces[3] = new Queen(1, 4, 0);
	pieces[4] = new King(1, 5, 0);
	pieces[27] = new Queen(8, 4, 1);
	pieces[28] = new King(8, 5, 1);
	pieces[0] = new Rook(1, 2, 0);
	for(int p = 31; p > 17; p -= 7){
		pieces[p] = new Rook(8, p - 23, 1);
		pieces[p - 24] = new Rook(1, p - 23, 0);
	}

	for(int p = 30; p > 20; p -= 5){
		pieces[p] = new Knight(8, p - 23, 1);
		pieces[p - 24] = new Knight(1, p - 23, 0);
	}
	for(int p = 29; p > 23; p -= 3){
		pieces[p] = new Bishop(8, p - 23, 1);
		pieces[p - 24] = new Bishop(1, p - 23, 0);
	}
	for(int p = 8; p < 16; p++){
		pieces[p] = new Pawn(2, p - 7, 0);
	}
	for(int p = 16; p < 24; p++){
		pieces[p] = new Pawn(7, p - 15, 1);
	}

	//chessboard ornament init:

	for(int i = 0; i <= BOARD_COORD_MAX; i++){
		vector <char> replacer;
		board.push_back(replacer);
	}

	for(int x = 0; x <= BOARD_COORD_MAX; x++){
		board[x].push_back('0' + (9 - x));
		if(!x){
			for(int y = 0; y <= BOARD_COORD_MAX; y++){
				board[x].push_back(y + 97);
			}
		}
		else{
			for(int y = 0; y <= BOARD_COORD_MAX; y++){
				if((y + x) % 2){
					board[x].push_back(220);
				}
				else{
					board[x].push_back(' ');
				}
			}
		}
	}
	pathing.resize(pieces.size());
	for(int p = 0; p < pieces.size(); p++){
		vector <pair<int, int>> replacer;
		pathing[p] = replacer;
	}
	board[0][0] = '/';
}

Board::~Board(){
	for(int i = 0; i < pieces.size(); i++){
		delete pieces[i];
	}
}

void Board::drawBoard(){

	//chessboard pieces insert:

	for(int p = 0 ; p < pieces.size(); p++){
		if(pieces[p]->is_alive){
			board[pieces[p]->x_y.first][pieces[p]->x_y.second] = type_to_disp[pieces[p]->type];
		}

	}

	//actual drawing

	for(int x = 0; x <= BOARD_COORD_MAX; x++){
		for(int y = 0; y <= BOARD_COORD_MAX; y++){
			cout << ' ' << board[x][y];
		}
		cout << endl;
	}
}

void Board::clearBoard(bool prev_err){
	int offset = 1;
	if(!prev_err){
		offset = 0;
		cout << "\x1b[1A\x1b[1A\x1b[1A\x1b[1A";
	}
	for(int x = 0; x < BOARD_COORD_MAX + offset; x++){
		cout << "\x1b[2K" << "\x1b[1A";
	}
}

void Board::clearError(bool prev_err){
	int err_len = 2;
	if(prev_err){
		err_len += 3;
	}
	for(int x = 0; x <= err_len; x++){
		cout << "\x1b[2K" << "\x1b[1A";
	}
}
void Board::spawnGame(Player& player_1, Player& player_2){

	//introduction

	string w = "whites", b = "blacks";
	cout << "The Gods Of RNG have decided that...\n" << player_1.name << " is now affiliated with the ";
	if(player_1.side){
		cout << w;
	}
	else{
		cout << b;
	}
	cout << "\n and " << player_2.name << " is going to combat for the ";
	if(player_2.side){
		cout << w;
	}
	else{
		cout << b;
	}
	cout << ". Let the games begin.\n" << endl;

	bool victory = 0, prev_err = 0;
	string command;
	pair <int, int> kills = {0, 0}, moves = {0, 0}; //.first -> white, .second -> black
	while(true){

		Player current_player;
		int current_piece_index = -1, current_target_index = -1;
		pair <int, int> from = {0, 0}, to = {0 ,0};

		drawBoard();

		//player turn announcement 

		if(player_1.turn){
			cout << "It's " << player_1.name << "'s turn." << endl;
			current_player = player_1;
		}
		else if(player_2.turn){
			cout << "It's " << player_2.name << "'s turn." << endl;
			current_player = player_2;
		}
		else{
			cerr << "Boss, I think we have ourselves some extra company." << endl;
			break;
		}


		//accepting user input move

		cout << "Enter your move, " << current_player.name << '.' << endl;
		getline(cin, command);

		try{
			isTheCommandLegal(command);
			pair <char, int> repl_from = {command[0], command[1] - '0'}, repl_to = {command[3], command[4] - '0'};
			from = transformXY(repl_from);
			to = transformXY(repl_to);
		}
		catch(IllegalInput err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}
		catch(OutOfBoundsCoordinates err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}


		//piece action!

		try{
			current_piece_index = findPiece(from, current_player.side);
			current_target_index = findTarget(to, current_player.side);

			//kill the target piece, if there is a piece in the target square+move the selected piece to a new position

			if(current_target_index >= 0){
				pieces[current_target_index]->is_alive = !pieces[current_target_index]->is_alive; //GILL IT
				pieces[current_target_index]->x_y = {-1, -1}; //remove the pieces from the board ENTRIRELY
				if(pieces[current_target_index]->side){
					kills.second++;
				}
				else{
					kills.first;
				}
			}
			checkCollision(from, to);
			pieces[current_piece_index]->move(to.first, to.second);

			if(pieces[current_piece_index]->side){
				moves.first++;
			}
			else{
				moves.second++;
			}
			//memorizing path for each piece

			pathing[current_piece_index].push_back(to);
		}
		catch(TargetingEmptyPosition err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();  
			continue;
		}
		catch(TargetingEnemyPiece err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}
		catch(IllegalMove err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}
		catch(SandbagMove err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}
		catch(ObstructedPath err){
			clearError(prev_err);
			prev_err = 1;
			clearBoard(1);
			err.what();
			continue;
		}


		// redraw the board under the moved pieces:

		if((from.first + from.second) % 2 != 0){
			board[from.first][from.second] = ' ';
		}
		else{
			board[from.first][from.second] = 220;
		}










		//clear the board

		clearBoard(0);

		//turn switch

		player_1.turn = !player_1.turn;
		player_2.turn = !player_2.turn;

		//end of game check

		if(!pieces[4]->is_alive){
			victory = 1;
			break;
		}
		else if(!pieces[28]->is_alive){
			victory = 0;
break;
		}
	}
	if(victory){
		cout << "The Whites win." << endl;
	}
	else{
		cout << "The Blacks win." << endl;
	}
	cout << "\nTotal pieces destroyed by the Whites side are equal " << kills.first << ", and the same for the Blacks is amounted to " << kills.second << ".\n" << endl;
	cout << "\nTotal moves by the Whites side are equal " << moves.first << ", and the same for the Blacks is amounted to " << moves.second << ".\n" << endl;
	cout << "\n Pathing for each figure:\n" << endl;
	for(int p = 0; p < pathing.size(); p++){
		for(int xy = 0; xy < pathing[p].size(); xy++){
			cout << '{' << pathing[p][xy].first << ", " << pathing[p][xy].second << '}';
		}
		cout << endl;
	}
	cout << "\nThis game is over, Humans. Feel free to restart me and try again." << endl;
}

bool Board::isTheCommandLegal(string c){
	if(c.size() != 5 || c[2] != '-'){
		throw IllegalInput();
		return 0;
	}
	else{
		return 1;
	}
}

pair <int, int> Board::transformXY(pair <char, int> x_y){
	Pawn replacer(1, 1, 1);
	pair <int, int> true_x_y;
	true_x_y.first = 9 - x_y.second;
	true_x_y.second = x_y.first - 96;
	if(replacer.checkNotOutOfBound(true_x_y)){
		return true_x_y;
	}
	else{
		throw OutOfBoundsCoordinates();
	}
}

int Board::findPiece(pair <int, int> xy, bool side){
	int ind = -1;
	for(int i = 0; i < pieces.size(); i++){
		if(pieces[i]->x_y == xy){
			ind = i;
		}
	}
	if(ind == -1){
		throw TargetingEmptyPosition();
	}
	else if(pieces[ind]->side != side){
		throw TargetingEnemyPiece();
	}
	else{
		return ind;
	}

}

int Board::findTarget(pair <int, int> xy, bool side){
	int ind = -1;
	for(int i = 0; i < pieces.size(); i++){
		if(pieces[i]->x_y == xy){
			ind = i;
		}
	}
	if(ind >= 0 && (pieces[ind]->side == side)){
		throw SandbagMove();
	}
	return ind;
}

bool Board::checkCollision(pair<int, int> from, pair<int, int> to){

	if(from.first == to.first){ //horizontal movement DETECTED!
		int x = from.first;
		for(int y = (from.first < to.first ? from.first : to.first) + 1;
			y <= (from.first > to.first ? from.first : to.first) - 1;
			y++){
			if((board[x][y] != (char)220) && (board[x][y] != ' ')){
				throw ObstructedPath();
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	else if(from.second == to.second){ //vertical movement DETECTED!
		int y = from.second;
		for(int x = (from.first < to.first ? from.first : to.first) + 1;
			x <= (from.first > to.first ? from.first : to.first) - 1;
			x++){
			if((board[x][y] != (char)220) && (board[x][y] != ' ')){
				throw ObstructedPath();
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	else if(from.first + from.second == to.first + to.second){ //main diagonal movement DETECTED! 
		for(int x = (from.first < to.first ? from.first : to.first) + 1;
			x <= (from.first > to.first ? from.first : to.first) - 1;
			x++){
			if((board[x][(from.first + from.second - x)] != (char)220) && (board[x][(from.first + from.second - x)] != ' ')){
				throw ObstructedPath();
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	else if(from.first - from.second == to.first - to.second){ //submain diagonal movement DETECTED!
		for(int x = (from.first < to.first ? from.first : to.first) + 1;
			x <= (from.first > to.first ? from.first : to.first) - 1;
			x++){
			if((board[x][abs((from.first - from.second) - x)] != (char)220) && (board[x][abs(from.first - from.second - x)] != ' ')){
				throw ObstructedPath();
				return 1;
			}
			else{
				return 0;
			}
		}
	}
}