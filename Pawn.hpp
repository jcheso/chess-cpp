#ifndef PAWN_HPP
#define PAWN_HPP
#include "ChessPiece.hpp"
#include <string>
class Pawn : public ChessPiece
{
public:
    Pawn(char colour);
    ~Pawn();

private:
    std::string name = "Pawn";
};

#endif
