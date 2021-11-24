#include "King.hpp"
#include "ChessPiece.hpp"
#include <string>

King::King(char colour, std::string name) : ChessPiece(colour, name) {}
King::~King() {}
bool King::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) { return false; }