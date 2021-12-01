#include "Bishop.h"
#include "ChessPiece.h"
#include <string>

Bishop::Bishop(char colour, std::string name) : ChessPiece(colour, name) {}
bool Bishop::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the move is diagonal and that the path is clear
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb) && fromFile != toFile && fromRank != toRank)
        return true;
    else
        return false;
}