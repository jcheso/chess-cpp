#ifndef ROOK_HPP
#define ROOK_HPP
#include "ChessPiece.hpp"
#include <string>

class Rook : public ChessPiece
{
public:
    Rook(char colour);
    ~Rook();

private:
    std::string name = "Rook";
};

#endif
