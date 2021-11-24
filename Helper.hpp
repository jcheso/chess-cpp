#ifndef HELPER_HPP
#define HELPER_HPP
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include <iostream>
using namespace std;

enum File
{
    F_A,
    F_B,
    F_C,
    F_D,
    F_E,
    F_F,
    F_G,
    F_H,
};

enum Rank
{
    R_1,
    R_2,
    R_3,
    R_4,
    R_5,
    R_6,
    R_7,
    R_8,
};

#endif
