#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP
class ChessBoard;
#include "ChessPiece.hpp"
using namespace std;

class ChessBoard
{
private:
    ChessPiece *board[8][8];
    bool isWhiteTurn;
    bool isGameComplete;
    bool isStalemate();
    void resetGame();
    void printBoard();

public:
    ChessBoard();
    ~ChessBoard();

    ChessPiece *getChessPiece(int rank, int file);
};

#endif
