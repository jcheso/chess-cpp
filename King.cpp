#include "King.h"
#include "ChessPiece.h"
#include <string>

King::King(char colour, std::string name) : ChessPiece(colour, name) {}
King::~King() {}
bool King::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the path is clear and it is a magnitude of 1 - direction does not matter for King
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb) && ((fromFile - toFile) == abs(1) || (fromRank - toRank) == abs(1)))
        return true;
    else
        return false;
}