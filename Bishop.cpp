#include "Bishop.h"
#include "ChessPiece.h"
#include <string>

Bishop::Bishop(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Bishop::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the move is diagonal and that the path is clear
    if (thisPiece->isPathClear(toRank, toFile, cb) && currentFile != toFile && currentRank != toRank)
        return true;
    else
        return false;
}