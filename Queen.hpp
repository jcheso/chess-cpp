#ifndef QUEEN_HPP
#define QUEEN_HPP
#include "ChessPiece.hpp"
#include <string>

class Queen : public ChessPiece
{
public:
    Queen(char colour, std::string name);
    ~Queen();
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

private:
};

#endif
