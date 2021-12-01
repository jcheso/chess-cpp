#ifndef ROOK_H
#define ROOK_H
#include <string>

#include "ChessPiece.h"

class Rook : public ChessPiece {
   public:
    Rook(int colour, std::string name, int rank, int file);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
