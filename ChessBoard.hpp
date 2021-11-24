#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP
class ChessPiece;
#include "ChessPiece.hpp"
#include <string>

class ChessBoard
{
private:
    ChessPiece *board[8][8];
    bool isWhiteTurn = true;
    bool isGameComplete;
    bool isStalemate();
    void resetGame();
    void printBoard();
    void makeMove();
    void addPiece();
    void removePiece();
    void setBoard();

public:
    ChessBoard();
    ~ChessBoard();
    bool submitMove(std::string moveFrom, std::string moveTo);
    ChessPiece *getChessPiece(int rank, int file);
};

#endif
