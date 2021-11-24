#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "ChessPiece.hpp"
#include <string>
class Knight : public ChessPiece
{
public:
    Knight(char colour, std::string name);
    ~Knight();
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

private:
};

#endif
