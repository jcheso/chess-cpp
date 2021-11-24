#include "Bishop.hpp"
#include "ChessPiece.hpp"
#include <string>

Bishop::Bishop(char colour, std::string name) : ChessPiece(colour, name) {}
Bishop::~Bishop() {}
bool Bishop::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) { return false; }