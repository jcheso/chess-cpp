#include "Bishop.hpp"
#include "ChessPiece.hpp"
#include <string>

Bishop::Bishop(char colour, std::string name) : ChessPiece(colour, name) {}
Bishop::~Bishop() {}
bool Bishop::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);

    // Check the move is diagonal and that the squares in between the origin and target are free
    // if (targetPosition->getName() == "Free")
    // {
    //     }

    return false;
}