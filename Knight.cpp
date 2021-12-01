#include "Knight.h"
#include "ChessPiece.h"
#include <string>

Knight::Knight(char colour, std::string name) : ChessPiece(colour, name) {}
bool Knight::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    if (((abs(fromRank - toRank) + abs(fromFile - toFile)) == 3) && fromRank != toRank && fromFile != toFile)
        return true;
    else
        return false;
}