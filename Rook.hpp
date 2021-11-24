#ifndef ROOK_HPP
#define ROOK_HPP
#include "ChessPiece.hpp"
using namespace std;

class Rook : public ChessPiece
{
public:
    Rook(char colour);
    ~Rook();

private:
    virtual char getPiece();
};

#endif
