#include "King.hpp"
using namespace std;

King::King(char colour) : ChessPiece(colour) {}
King::~King() {}

char King::getPiece()
{
    return 'K';
}
