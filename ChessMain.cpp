#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Helper.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include <iostream>
using namespace std;

int main()
{

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;

	// ** PAWN UNIT TESTS **
	// // Test White pawn can move forward by 2
	// cout << '\n';
	// cb.submitMove("A2", "A4");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test Black pawn can move forward by 2
	// cb.submitMove("B7", "B5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test White pawn can move forward by 1
	// cb.submitMove("B2", "B3");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test Black pawn can move forward by 1
	// cb.submitMove("C7", "C6");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test White pawn cannot move diagonal by 2
	// cb.submitMove("C2", "D4");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test White pawn cannot move diagonal by 1
	// cb.submitMove("C2", "D3");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move white
	// cb.submitMove("C2", "C3");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test Black pawn cannot move diagonal by 1
	// cb.submitMove("C6", "D5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move black
	// cb.submitMove("C6", "C5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test White pawn cannot move backwards
	// cb.submitMove("B3", "B2");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move white
	// cb.submitMove("B3", "B4");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test Black pawn cannot move backwards
	// cb.submitMove("C5", "C6");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move black
	// cb.submitMove("C5", "C4");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test White pawn can take black pawn
	// cb.submitMove("A4", "B5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move black
	// cb.submitMove("H7", "H5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Move white
	// cb.submitMove("D2", "D3");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test black pawn can take white pawn
	// cb.submitMove("C4", "D3");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';
	// // Test white pawn cannot move sideways
	// cb.submitMove("B5", "C5");
	// cout << '\n';
	// cb.printBoard();
	// cout << '\n';

	cout << '\n';
	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n';
	cb.printBoard();
	cout << '\n';

	// cout << "=========================\n";
	// cout << "Alekhine vs. Vasic (1931)\n";
	// cout << "=========================\n\n";

	// cb.resetBoard();
	// cout << '\n';

	// cb.submitMove("E2", "E4");
	// cb.submitMove("E7", "E6");
	// cout << '\n';

	// cb.submitMove("D2", "D4");
	// cb.submitMove("D7", "D5");
	// cout << '\n';

	// cb.submitMove("B1", "C3");
	// cb.submitMove("F8", "B4");
	// cout << '\n';

	// cb.submitMove("F1", "D3");
	// cb.submitMove("B4", "C3");
	// cout << '\n';

	// cb.submitMove("B2", "C3");
	// cb.submitMove("H7", "H6");
	// cout << '\n';

	// cb.submitMove("C1", "A3");
	// cb.submitMove("B8", "D7");
	// cout << '\n';

	// cb.submitMove("D1", "E2");
	// cb.submitMove("D5", "E4");
	// cout << '\n';

	// cb.submitMove("D3", "E4");
	// cb.submitMove("G8", "F6");
	// cout << '\n';

	// cb.submitMove("E4", "D3");
	// cb.submitMove("B7", "B6");
	// cout << '\n';

	// cb.submitMove("E2", "E6");
	// cb.submitMove("F7", "E6");
	// cout << '\n';

	// cb.submitMove("D3", "G6");
	// cout << '\n';

	return 0;
}
