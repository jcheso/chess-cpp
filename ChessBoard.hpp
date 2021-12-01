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
    void makeMove();
    void addPiece();
    void removePiece();
    void setBoard();
    void clearBoard();
    void getKingCoordinates(int &kingRank, int &kingFile, char colour);

public:
    ChessBoard();
    ~ChessBoard();
    bool submitMove(std::string moveFrom, std::string moveTo);
    void printBoard();
    void resetBoard();
    bool isCheck();
    bool isCheckmate();
    bool isKingInCheck(int rankToCheck, int fileToCheck, char oppositeTeam);
    ChessPiece *getChessPiece(int rank, int file);
};

#endif
