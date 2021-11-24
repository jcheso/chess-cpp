#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include <iostream>
using namespace std;

// ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
ChessPiece::ChessPiece(char colour) : colour(colour) {}
ChessPiece::~ChessPiece() {}

// ** GETTERS **
char ChessPiece::getColour() { return this->colour; }
char ChessPiece::getPiece() { return '.'; }
bool ChessPiece::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {}
bool ChessPiece::isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // Create a pointer to the piece(or empty spot) on the board
    ChessPiece *newPosition = cb->getChessPiece(toRank, toFile);
    // If the position is the opposite player or is empty, check if the move is valid for the specific piece
    if (newPosition->getPiece() == '.' || this->colour != newPosition->getColour())
        return isLegalMove(fromRank, fromFile, toRank, toFile, cb);
    else
    {
        cerr << "Not a valid move, try again!" << endl;
        return false;
    }
}
