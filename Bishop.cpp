#include "Bishop.hpp"
using namespace std;

Bishop::Bishop(char colour) : ChessPiece(colour) {}
Bishop::~Bishop() {}

char Bishop::getPiece()
{
    return 'B';
}
