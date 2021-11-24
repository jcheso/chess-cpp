#include "Rook.hpp"
#include "ChessPiece.hpp"
#include <string>

Rook::Rook(char colour, std::string name) : ChessPiece(colour, name) {}
Rook::~Rook() {}
bool Rook::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {}