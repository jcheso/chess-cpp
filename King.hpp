#ifndef KING_HPP
#define KING_HPP
#include "ChessPiece.hpp"
using namespace std;

class King : public ChessPiece
{
public:
    King(char colour);
    ~King();

private:
    virtual char getPiece();
};

#endif
