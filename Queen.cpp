#include "Queen.hpp"
using namespace std;

Queen::Queen(char colour) : ChessPiece(colour) {}
Queen::~Queen() {}

char Queen::getPiece()
{
    return 'Q';
}
