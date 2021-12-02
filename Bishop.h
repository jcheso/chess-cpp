#ifndef BISHOP_H
#define BISHOP_H
#include <string>

#include "ChessPiece.h"
#include "Helper.h"
class Bishop : public ChessPiece {
   public:
    Bishop(int colour, std::string name, int rank, int file);
    bool isLegalMove(int toRank, int toFile, ChessBoard *cb) override;
};

#endif
