#ifndef KING_H
#define KING_H
#include "ChessPiece.h"
using namespace std;

class King : public ChessPiece
{
public:
    King(char colour, std::string name);
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) override;

private:
};

#endif