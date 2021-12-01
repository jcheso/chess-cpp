#ifndef KNIGHT_H
#define KNIGHT_H
#include "ChessPiece.h"
#include <string>
class Knight : public ChessPiece
{
public:
    Knight(char colour, std::string name);
    bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;

private:
};

#endif