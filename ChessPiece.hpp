#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP
class ChessBoard;
#include "ChessBoard.hpp"
#include <string>

class ChessPiece
{
private:
    // Check if the move is legal for the specific piece
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    std::string name;
    char colour;

public:
    // ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
    ChessPiece(char colour, std::string name);
    ~ChessPiece();
    // Get the name of the piece

    std::string getName();
    // ** GETTERS **
    // Get the colour of the piece
    char getColour();

    // Check if the move is valid (i.e. empty spot and not the same colour) and call isLegalMove()
    bool isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
};

#endif
