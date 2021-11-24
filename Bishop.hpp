#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "ChessPiece.hpp"
#include "Helper.hpp"
#include <string>
class Bishop : public ChessPiece
{
public:
    Bishop(char colour, std::string name);
    ~Bishop();
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
};

#endif
