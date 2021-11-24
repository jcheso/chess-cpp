#include "Knight.hpp"
using namespace std;

Knight::Knight(char colour) : ChessPiece(colour) {}
Knight::~Knight() {}

char Knight::getPiece()
{
    return 'k';
}
