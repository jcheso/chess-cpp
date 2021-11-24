#ifndef QUEEN_HPP
#define QUEEN_HPP
#include "ChessPiece.hpp"
using namespace std;

class Queen : public ChessPiece
{
public:
    Queen(char colour);
    ~Queen();

private:
    virtual char getPiece();
};

#endif
