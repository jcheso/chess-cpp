#include "Rook.h"
#include "ChessPiece.h"
#include <string>

Rook::Rook(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Rook::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the path is clear and the move is either in horizontal (same rank) or vertical (same file)
    if (thisPiece->isPathClear(toRank, toFile, cb) && ((currentFile == toFile) || (currentRank == toRank)))
    {
        return true;
    }

    return false;
}