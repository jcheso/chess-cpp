#ifndef PAWN_HPP
#define PAWN_HPP
#include "ChessPiece.hpp"
#include <string>
class Pawn : public ChessPiece
{
public:
    Pawn(char colour, std::string name);
    ~Pawn();
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

private:
};

#endif
