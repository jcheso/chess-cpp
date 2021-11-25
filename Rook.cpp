#include "Rook.hpp"
#include "ChessPiece.hpp"
#include <string>

Rook::Rook(char colour, std::string name) : ChessPiece(colour, name) {}
Rook::~Rook() {}
bool Rook::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);

    // Check the path is clear and the move is either in horizontal (same rank) or vertical (same file)
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb) && ((fromFile == toFile) || (fromRank == toRank)))
    {
        return true;
    }

    return false;
}