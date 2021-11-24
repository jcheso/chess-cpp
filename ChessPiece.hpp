#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP
class ChessBoard;
#include "ChessBoard.hpp"
#include <string>

class ChessPiece
{
private:
    // Check if the move is legal for the specific piece
    std::string name;
    char colour;

protected:
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

public:
    // ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
    ChessPiece(char colour, std::string name);
    ~ChessPiece();

    // ** GETTERS **
    // Get the name of the piece
    std::string getName();
    // Get the colour of the piece
    char getColour();
    // Check if the move is valid (i.e. empty spot and not the same colour) and call isLegalMove()
    bool isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
};

#endif
