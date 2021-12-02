#include "Bishop.h"

#include <string>

#include "ChessPiece.h"

Bishop::Bishop(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Bishop::isLegalMove(int toRank, int toFile, ChessBoard *cb) {
    if (isPathClear(toRank, toFile, cb) && (abs(currentRank - toRank) == abs(currentFile - toFile)))
        return true;
    else
        return false;
}