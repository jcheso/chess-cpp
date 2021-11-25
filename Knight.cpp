#include "Knight.hpp"
#include "ChessPiece.hpp"
#include <string>

Knight::Knight(char colour, std::string name) : ChessPiece(colour, name) {}
Knight::~Knight() {}
bool Knight::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    if ((abs(fromRank - toRank) + abs(fromFile - toFile)) == 3)
        return true;
    else
        return false;
}