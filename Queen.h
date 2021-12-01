#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
#include <string>

class Queen : public ChessPiece
{
public:
    Queen(char colour, std::string name);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
