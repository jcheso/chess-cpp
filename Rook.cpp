#include "Rook.h"

#include <string>

#include "ChessPiece.h"

Rook::Rook(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Rook::isLegalMove(int toRank, int toFile, ChessBoard *cb) {
    // Check the path is clear and the move is either in horizontal (same rank) or vertical (same file)
    if (isPathClear(toRank, toFile, cb) && ((currentFile == toFile) || (currentRank == toRank))) {
        return true;
    }

    return false;
}