#include "Queen.h"
#include "ChessPiece.h"
#include <string>

Queen::Queen(int colour, std::string name) : ChessPiece(colour, name) {}
bool Queen::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the path is clear and the move is on the same diagonal
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb))
        return true;
    else
        return false;
}