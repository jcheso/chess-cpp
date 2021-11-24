#include "Pawn.hpp"
#include "ChessPiece.hpp"
#include <string>
#include <iostream>

Pawn::Pawn(char colour, std::string name) : ChessPiece(colour, name) {}
Pawn::~Pawn() {}
bool Pawn::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    ChessPiece *thisPiece = cb->getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);
    // If the target position is empty
    if (targetPosition->getName() == "Free")
    {
        // Check the move is only 1 rank in up direction for white and down for black, or 2 if it's the first move of the pawn
        if (thisPiece->getColour() == 'W')
        {
            if ((toRank == fromRank + 1) || (thisPiece->isFirstMove && (toRank == fromRank + 2)))
                return true;
        }
        else
        {
            if ((toRank == fromRank - 1) || (thisPiece->isFirstMove && (toRank == fromRank - 2)))
                return true;
        }
    }
    // If the target position has the other player
    else
    {
        // Check the move is diagonal by 1 file
        if ((toFile == fromFile + 1) || (toFile == fromFile - 1))
        {
            // Check the move is only 1 rank in up direction for white and down for black
            if (thisPiece->getColour() == 'W')
            {
                if (toRank == fromRank + 1)
                    return true;
            }
            else
            {
                if (toRank == fromRank - 1)
                    return true;
            }
        }
    }
    return false;
}
