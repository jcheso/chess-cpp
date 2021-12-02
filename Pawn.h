#ifndef PAWN_H
#define PAWN_H
#include <string>

#include "ChessPiece.h"
class Pawn : public ChessPiece {
   public:
    Pawn(int colour, std::string name, int rank, int file);
    bool isFirstMove();
    bool isLegalMove(int toRank, int toFile, ChessBoard *cb) override;
};

#endif
