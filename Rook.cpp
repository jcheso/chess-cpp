#include "Rook.h"
#include "ChessPiece.h"
#include <string>

Rook::Rook(char colour, std::string name) : ChessPiece(colour, name) {}
bool Rook::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the path is clear and the move is either in horizontal (same rank) or vertical (same file)
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb) && ((fromFile == toFile) || (fromRank == toRank)))
    {
        return true;
    }

    return false;
}