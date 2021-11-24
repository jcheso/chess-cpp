#include "ChessPiece.hpp"
#include <iostream>
#include <string>

// ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
ChessPiece::ChessPiece(char colour, std::string name) : colour(colour), name(name) {}
ChessPiece::~ChessPiece() {}

// ** GETTERS **
char ChessPiece::getColour() { return this->colour; }
std::string ChessPiece::getName() { return this->name; }
bool ChessPiece::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {}
bool ChessPiece::isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // Create a pointer to the piece(or empty spot) on the board
    ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);
    // If the position is the opposite player or is empty, check if the move is valid for the specific piece
    if (targetPosition->getName() == "Free" || this->colour != targetPosition->getColour())
        return isLegalMove(fromRank, fromFile, toRank, toFile, cb);
    else
        return false;
}
