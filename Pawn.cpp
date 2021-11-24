#include "Pawn.hpp"
using namespace std;

Pawn::Pawn(char colour) : ChessPiece(colour) {}
Pawn::~Pawn() {}

char Pawn::getPiece()
{
    return 'P';
}
