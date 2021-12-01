#ifndef PAWN_H
#define PAWN_H
#include "ChessPiece.h"
#include <string>
class Pawn : public ChessPiece
{
public:
    Pawn(int colour, std::string name, int rank, int file);
    bool isFirstMove(int fromRank);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
