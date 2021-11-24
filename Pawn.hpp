#ifndef PAWN_HPP
#define PAWN_HPP
#include "ChessPiece.hpp"
using namespace std;

class Pawn : public ChessPiece
{
public:
    Pawn(char colour);
    ~Pawn();

private:
    virtual char getPiece();
};

#endif
