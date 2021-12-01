#include "Queen.h"

#include <string>

#include "ChessPiece.h"

Queen::Queen(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Queen::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the path is clear and the move is on the same diagonal
    if (thisPiece->isPathClear(toRank, toFile, cb))
        return true;
    else
        return false;
}