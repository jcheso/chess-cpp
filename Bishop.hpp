#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "ChessPiece.hpp"
using namespace std;

class Bishop : public ChessPiece
{
public:
    Bishop(char colour);
    ~Bishop();

private:
    virtual char getPiece();
};

#endif
