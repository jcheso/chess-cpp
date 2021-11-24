#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "ChessPiece.hpp"
#include "Helper.hpp"
#include <string>
class Bishop : public ChessPiece
{
public:
    Bishop(char colour);
    ~Bishop();

private:
    std::string name = "Bishop";
};

#endif
