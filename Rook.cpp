#include "Rook.hpp"
using namespace std;

Rook::Rook(char colour) : ChessPiece(colour) {}
Rook::~Rook() {}

char Rook::getPiece()
{
    return 'R';
}
