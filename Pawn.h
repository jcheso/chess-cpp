#ifndef PAWN_H
#define PAWN_H
#include <string>

#include "ChessPiece.h"
class Pawn : public ChessPiece {
   public:
    Pawn(int colour, std::string name, int rank, int file);
    bool isFirstMove(int fromRank);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
