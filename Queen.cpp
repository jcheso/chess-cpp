#include "Queen.hpp"
#include "ChessPiece.hpp"
#include <string>

Queen::Queen(char colour, std::string name) : ChessPiece(colour, name) {}
Queen::~Queen() {}
bool Queen::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {}