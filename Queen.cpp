#include "Queen.h"

#include <string>

#include "ChessPiece.h"

Queen::Queen(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Queen::isLegalMove(int toRank, int toFile, ChessBoard *cb) {
    // Check the path is clear and the move is on the same diagonal
    if (isPathClear(toRank, toFile, cb))
        return true;
    else
        return false;
}