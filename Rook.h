#ifndef ROOK_H
#define ROOK_H
#include "ChessPiece.h"
#include <string>

class Rook : public ChessPiece
{
public:
    Rook(char colour, std::string name);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;

private:
};

#endif
