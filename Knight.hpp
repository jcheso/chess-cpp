#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "ChessPiece.hpp"
using namespace std;

class Knight : public ChessPiece
{
public:
    Knight(char colour);
    ~Knight();

private:
    virtual char getPiece();
};

#endif
