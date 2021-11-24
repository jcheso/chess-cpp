#ifndef QUEEN_HPP
#define QUEEN_HPP
#include "ChessPiece.hpp"
#include <string>

class Queen : public ChessPiece
{
public:
    Queen(char colour);
    ~Queen();

private:
    std::string name = "Queen";
};

#endif
