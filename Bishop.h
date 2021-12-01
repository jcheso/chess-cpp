#ifndef BISHOP_H
#define BISHOP_H
#include "ChessPiece.h"
#include "Helper.h"
#include <string>
class Bishop : public ChessPiece
{
public:
    Bishop(char colour, std::string name);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;
};

#endif
