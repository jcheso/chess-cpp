#ifndef KNIGHT_H
#define KNIGHT_H
#include <string>

#include "ChessPiece.h"
class Knight : public ChessPiece {
   public:
    Knight(int colour, std::string name, int rank, int file);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
