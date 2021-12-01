#include "Knight.h"
#include "ChessPiece.h"
#include <string>

Knight::Knight(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}
bool Knight::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    if (((abs(fromRank - toRank) + abs(fromFile - toFile)) == 3) && fromRank != toRank && fromFile != toFile)
        return true;
    else
        return false;
}