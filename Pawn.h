#ifndef PAWN_H
#define PAWN_H
#include "ChessPiece.h"
#include <string>
class Pawn : public ChessPiece
{
public:
    Pawn(char colour, std::string name);
    bool isFirstMove(int fromRank);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
