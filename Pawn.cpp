#include "Pawn.hpp"
#include "ChessPiece.hpp"
#include <string>
#include <iostream>

Pawn::Pawn(char colour, std::string name) : ChessPiece(colour, name) {}
Pawn::~Pawn() {}
bool Pawn::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // If the target position is empty
    std::cout << "Testing we get here" << std::endl;
    // If the target position has the other player
}
