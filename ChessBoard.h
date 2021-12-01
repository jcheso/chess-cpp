#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
class ChessPiece;
#include "ChessPiece.h"
#include <string>

class ChessBoard
{
private:
    // ** VARIABLES **
    bool isWhiteTurn = true;
    ChessPiece *board[8][8];

    // ** GETTERS **
    void getKingCoordinates(int &kingRank, int &kingFile, int colour);
    bool isCheck();
    bool isKingInCheck(int rankToCheck, int fileToCheck, char oppositeTeam);
    bool isCheckmate();
    bool isStalemate();

    // ** SETTERS **
    void setBoard();
    void clearBoard();
    void makeMove();
    void addPiece();
    void removePiece();

public:
    ChessBoard();
    ~ChessBoard();

    // ** GETTERS **
    void printBoard();
    ChessPiece *getChessPiece(int rank, int file);

    // ** SETTERS **
    bool submitMove(std::string moveFrom, std::string moveTo);
    void resetBoard();
};

#endif
