#include "Bishop.hpp"
#include "ChessPiece.hpp"
#include <string>

Bishop::Bishop(char colour, std::string name) : ChessPiece(colour, name) {}
Bishop::~Bishop() {}
bool Bishop::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    // Check the move is diagonal and that the path is clear
    if (thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb) && fromFile != toFile)
        return true;
    else
        return false;
}