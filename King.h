#ifndef KING_H
#define KING_H
#include "ChessPiece.h"
using namespace std;

class King : public ChessPiece {
   public:
    King(int colour, std::string name, int rank, int file);
    virtual bool isLegalMove(int toRank, int toFile, ChessBoard *cb) override;
};

#endif
