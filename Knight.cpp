#include "Knight.h"

#include <string>

#include "ChessPiece.h"

Knight::Knight(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Knight::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {
    if (((abs(currentRank - toRank) + abs(currentFile - toFile)) == 3) && currentRank != toRank && currentFile != toFile)
        return true;
    else
        return false;
}