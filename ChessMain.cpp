#include <iostream>

#include "ChessPiece.h"
using namespace std;

int main() {
    // !! REFACTORING
    // TODO: DRY - Don't Repeat Yourself
    // TODO: Reduce Method Length to 10 lines where possible
    // TODO: Reduce parameter list to <5
    // TODO: Turn data clumps into classes
    // TODO: Check for alternative classes that do the same thing
    // TODO: Check for middle man classes
    // TODO: Create thorough unit tests for all pieces

    cout << "========================\n";
    cout << "Testing the Chess Engine\n";
    cout << "========================\n\n";

    ChessBoard cb;

    // **PRESET TESTS**
    cout << '\n';
    cb.submitMove("D7", "D6");
    cout << '\n';

    cb.submitMove("D4", "H6");
    cout << '\n';

    cb.submitMove("D2", "D4");
    cout << '\n';

    cb.submitMove("F8", "B4");
    cout << '\n';

    cout << "=========================\n";
    cout << "Alekhine vs. Vasic (1931)\n";
    cout << "=========================\n\n";

    cb.resetBoard();
    cout << '\n';

    cb.submitMove("E2", "E4");
    cb.submitMove("E7", "E6");
    cout << '\n';

    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << '\n';

    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << '\n';

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << '\n';

    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << '\n';

    cb.submitMove("C1", "A3");
    cb.submitMove("B8", "D7");
    cout << '\n';

    cb.submitMove("D1", "E2");
    cb.submitMove("D5", "E4");
    cout << '\n';

    cb.submitMove("D3", "E4");
    cb.submitMove("G8", "F6");
    cout << '\n';

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << '\n';

    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << '\n';

    cb.submitMove("D3", "G6");
    cout << '\n';

    cb.printBoard();

    cout << "========================\n";
    cout << "Testing for a Stalemate\n";
    cout << "========================\n\n";

    cb.resetBoard();

    cb.submitMove("C2", "C4");

    cb.submitMove("H7", "H5");

    cb.submitMove("H2", "H4");

    cb.submitMove("A7", "A5");

    cb.submitMove("D1", "A4");

    cb.submitMove("A8", "A6");

    cb.submitMove("A4", "A5");

    cb.submitMove("A6", "H6");

    cb.submitMove("A5", "C7");

    cb.submitMove("F7", "F6");

    cb.submitMove("C7", "D7");

    cb.submitMove("E8", "F7");

    cb.submitMove("D7", "B7");

    cb.submitMove("D8", "D3");

    cb.submitMove("B7", "B8");

    cb.submitMove("D3", "H7");

    cb.submitMove("B8", "C8");

    cb.submitMove("F7", "G6");

    cb.submitMove("C8", "E6");

    cb.resetBoard();
    // ** PAWN UNIT TESTS **
    cout << "Test White pawn can move forward by 2" << endl;
    cb.submitMove("A2", "A4");
    cb.printBoard();

    cout << "Test Black pawn can move forward by 2" << endl;
    cb.submitMove("B7", "B5");
    cb.printBoard();

    cout << "Test White pawn cannot move forward by 2" << endl;
    cb.submitMove("A4", "A6");
    cb.printBoard();

    cout << "Test White pawn cann move forward by 2" << endl;
    cb.submitMove("B2", "B4");
    cb.printBoard();

    // cout << "Test Black pawn cannot move forward by 2" << endl;
    // cb.submitMove("B5", "B3");
    // cb.printBoard();

    // cout << "Test Black pawn can take diagonal" << endl;
    // cb.submitMove("B5", "A4");
    // cb.printBoard();

    // // Test White pawn cannot move diagonal by 2
    // cb.submitMove("C2", "D4");
    // cb.printBoard();

    // // Test White pawn cannot move diagonal by 1
    // cb.submitMove("C2", "D3");
    // cb.printBoard();

    // // Move white
    // cb.submitMove("C2", "C3");
    // cb.printBoard();

    // // Test Black pawn cannot move diagonal by 1
    // cb.submitMove("C6", "D5");
    // cb.printBoard();

    // // Move black
    // cb.submitMove("C6", "C5");
    // cb.printBoard();

    // // Test White pawn cannot move backwards
    // cb.submitMove("B3", "B2");
    // cb.printBoard();

    // // Move white
    // cb.submitMove("B3", "B4");
    // cb.printBoard();

    // // Test Black pawn cannot move backwards
    // cb.submitMove("C5", "C6");
    // cb.printBoard();

    // // Move black
    // cb.submitMove("C5", "C4");
    // cb.printBoard();

    // // Test White pawn can take black pawn
    // cb.submitMove("A4", "B5");
    // cb.printBoard();

    // // Move black
    // cb.submitMove("H7", "H5");
    // cb.printBoard();

    // // Move white
    // cb.submitMove("D2", "D3");
    // cb.printBoard();

    // // Test black pawn can take white pawn
    // cb.submitMove("C4", "D3");
    // cb.printBoard();

    // // Test white pawn cannot move sideways
    // cb.submitMove("B5", "C5");
    // cb.printBoard();

    // // ** BISHOP UNIT TESTS **
    // cout << "Test White bishop can move diagonal" << endl;
    // cb.submitMove("C1", "A3");
    // cb.printBoard();

    // cout << "Test Bishop cannot move forward" << endl;
    // cb.submitMove("C8", "C7");
    // cb.printBoard();

    // cout << "Test Black Bishop can move diagonal" << endl;
    // cb.submitMove("C8", "B7");
    // cb.printBoard();

    // cout << "Test Bishop cannot move backward" << endl;
    // cb.submitMove("A3", "A2");
    // cb.printBoard();

    // cout << "Move white" << endl;
    // cb.submitMove("C3", "C4");
    // cb.printBoard();

    // cout << "Test Black Bishop can take white bishop" << endl;
    // cb.submitMove("B7", "G2");
    // cb.printBoard();

    // cout << "Test White Bishop cannot pass through" << endl;
    // cb.submitMove("A3", "C6");
    // cb.printBoard();

    // // ** ROOK UNIT TESTS **
    // cout << "Test white rook can move vertical" << endl;
    // cb.submitMove("A1", "A2");
    // cb.printBoard();

    // cout << "Test black rook vertical" << endl;
    // cb.submitMove("H8", "H6");
    // cb.printBoard();

    // cout << "Test white rook can move horizontal" << endl;
    // cb.submitMove("A2", "D2");
    // cb.printBoard();

    // cout << "Test black rook cant move diagonal" << endl;
    // cb.submitMove("H6", "G5");
    // cb.printBoard();

    // cout << "Test black rook can move horizontal" << endl;
    // cb.submitMove("H6", "A6");
    // cb.printBoard();

    // cout << "Test white rook can take black" << endl;
    // cb.submitMove("D2", "D3");
    // cb.printBoard();

    // cout << "Test black rook can take white" << endl;
    // cb.submitMove("A6", "A3");
    // cb.printBoard();

    // cout << "Test white rook can move backwards" << endl;
    // cb.submitMove("D3", "D2");
    // cb.printBoard();

    // // ** QUEEN UNIT TESTS **
    // cout << "Black Queen does not pass through diag" << endl;
    // cb.submitMove("D8", "F6");
    // cb.printBoard();

    // cout << "Move black pawn out way" << endl;
    // cb.submitMove("D7", "D5");
    // cb.printBoard();

    // cout << "Move white pawn out way" << endl;
    // cb.submitMove("D2", "D4");
    // cb.printBoard();

    // cout << "Black queen moves vertical" << endl;
    // cb.submitMove("D8", "D6");
    // cb.printBoard();

    // cout << "White queen doesn't pass sideways left" << endl;
    // cb.submitMove("E1", "D1");
    // cb.printBoard();

    // cout << "White queen doesn't pass sideways right" << endl;
    // cb.submitMove("D1", "F1");
    // cb.printBoard();

    // cout << "White queen moves vertical" << endl;
    // cb.submitMove("D1", "D3");
    // cb.printBoard();

    // cout << "Black queen moves diag" << endl;
    // cb.submitMove("D6", "B4");
    // cb.printBoard();

    // cout << "White queen moves diag" << endl;
    // cb.submitMove("D3", "F5");
    // cb.printBoard();

    // cout << "Black queen moves back" << endl;
    // cb.submitMove("B4", "B5");
    // cb.printBoard();

    // cout << "White queen moves up" << endl;
    // cb.submitMove("F5", "F6");
    // cb.printBoard();

    // // ** KING UNIT TESTS **
    // cout << "Black King does not pass through diag" << endl;
    // cb.submitMove("E8", "E7");
    // cb.printBoard();

    // cout << "Black King does not pass through right" << endl;
    // cb.submitMove("E8", "F8");
    // cb.printBoard();

    // cout << "Black King can move left" << endl;
    // cb.submitMove("E8", "D8");
    // cb.printBoard();

    // cout << "White King can move left" << endl;
    // cb.submitMove("E1", "D1");
    // cb.printBoard();

    // cout << "Black King can move diagonal" << endl;
    // cb.submitMove("D8", "C7");
    // cb.printBoard();

    // cout << "White King can move diagonal" << endl;
    // cb.submitMove("D1", "C2");
    // cb.printBoard();

    // // ** KNIGHT UNIT TESTS **
    // cout << "Black Knight takes Queen correctly" << endl;
    // cb.submitMove("G8", "F6");
    // cb.printBoard();

    // cout << "White knight cannot move big L" << endl;
    // cb.submitMove("G1", "E2");
    // cb.printBoard();

    // cout << "White knight can move legally over pieces" << endl;
    // cb.submitMove("G1", "F3");
    // cb.printBoard();

    // cout << "Black knight moves" << endl;
    // cb.submitMove("B8", "C6");
    // cb.printBoard();

    // cout << "White knight moves back" << endl;
    // cb.submitMove("F3", "G1");
    // cb.printBoard();

    return 0;
}
