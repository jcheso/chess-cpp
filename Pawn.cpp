#include "Pawn.hpp"
#include "ChessPiece.hpp"
#include <string>

Pawn::Pawn(char colour, std::string name) : ChessPiece(colour, name) {}
Pawn::~Pawn() {}
