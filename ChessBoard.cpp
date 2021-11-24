#include "ChessBoard.hpp"
#include "Helper.hpp"
using namespace std;

bool ChessBoard::isStalemate() {}
void ChessBoard::resetGame() {}
void ChessBoard::printBoard() {}

ChessBoard::ChessBoard()
{
    // Fill the board with Black Pieces
    for (int file = F_A; file < F_H; file++)
        board[R_7][file] = new Pawn('B');

    board[R_8][F_A] = new Rook('B');
    board[R_8][F_B] = new Knight('B');
    board[R_8][F_C] = new Bishop('B');
    board[R_8][F_D] = new King('B');
    board[R_8][F_E] = new Queen('B');
    board[R_8][F_F] = new Bishop('B');
    board[R_8][F_G] = new Knight('B');
    board[R_8][F_H] = new Rook('B');

    // Fill the board with White Pieces
    for (int file = F_A; file < F_H; file++)
        board[R_2][file] = new Pawn('B');

    board[R_1][F_A] = new Rook('B');
    board[R_1][F_B] = new Knight('B');
    board[R_1][F_C] = new Bishop('B');
    board[R_1][F_D] = new King('B');
    board[R_1][F_E] = new Queen('B');
    board[R_1][F_F] = new Bishop('B');
    board[R_1][F_G] = new Knight('B');
    board[R_1][F_H] = new Rook('B');

    // Fill the remainder of the board with nullptr
    for (int rank = R_3; rank < R_6; rank++)
    {
        for (int file = F_A; file < F_H; file++)
            board[rank][file] = new ChessPiece('.');
    }
    cout << "A new chess game is started!" << endl;
}

ChessBoard::~ChessBoard() {}
ChessPiece *ChessBoard::getChessPiece(int rank, int file)
{
    return this->board[rank][file];
}
