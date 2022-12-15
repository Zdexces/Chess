#include "horizon.h"
#include "Board.h"
#include "Player.h"
//#include <fcntl.h>
//#include <io.h>

/*
* TO DO LIST:
* 0)REFRESHABLE BOARD + SUICIDE PREVENTION!!!(DONE)
* 1)Piece collision(rough one, buddy)(ackccktually...kinda ez PEPEH))(DONE)
* 2)Piece death(KEKG)(DONE)
* 3)Check line immovability
* 4)Timer for both players(rough one, son)
* 5)Pawn tranformation(kinda rough one, sir)
* 6)Fix the bug with some lines of text(turn+move+input lines) still existing+check

*/

using std::cout;
using std::endl;

int main(){

    greet();

    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_int_distribution <int> side_sel(0, 1);
    bool side = side_sel(engine); 
    Player player_1(side), player_2(!side); 
    Board test;
    test.spawnGame(player_1, player_2);

    farewell();

    return 0;
}









////_setmode(_fileno(stdout), _O_U16TEXT);
//_setmode(_fileno(stdout), _O_U8TEXT);
//std::wcout << L"Testing unicode -- English -- Ελληνικά -- Español. -- ♚" << std::endl;
////std::cout << "u8\u265A";
//std::wcout << L"Hello, \u265A!\n";
//std::wstring symbol{ L"♚" };
//
//_setmode(_fileno(stdout), _O_WTEXT);
//std::wcout << symbol;