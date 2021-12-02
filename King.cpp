#include "King.h"

#include <string>

#include "ChessPiece.h"

King::King(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool King::isLegalMove(int toRank, int toFile, ChessBoard *cb) {
    // Check the path is clear and it is a magnitude of 1 - direction does not matter for King
    if (isPathClear(toRank, toFile, cb) && ((currentFile - toFile) == abs(1) || (currentRank - toRank) == abs(1)))
        return true;
    else
        return false;
}