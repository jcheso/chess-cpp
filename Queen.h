#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
#include <string>

class Queen : public ChessPiece
{
public:
    Queen(int colour, std::string name, int rank, int file);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
