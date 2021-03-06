#ifndef QUEEN_H
#define QUEEN_H
#include <string>

#include "ChessPiece.h"

class Queen : public ChessPiece {
   public:
    Queen(int colour, std::string name, int rank, int file);
    bool isLegalMove(int toRank, int toFile, ChessBoard *cb) override;
};

#endif
