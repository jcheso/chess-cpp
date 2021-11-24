#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP
class ChessPiece;
#include "ChessBoard.hpp"
using namespace std;

class ChessPiece
{
private:
    char colour;
    // Check if the move is legal for the specific piece
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

public:
    // ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
    ChessPiece(char colour);
    ~ChessPiece();

    // ** GETTERS **
    // Get the colour of the piece
    char getColour();
    // Get the name of the piece
    virtual char getPiece();
    // Check if the move is valid (i.e. empty spot and not the same colour) and call isLegalMove()
    bool isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
};

#endif
