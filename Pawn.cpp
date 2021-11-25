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

    // If the target position is empty ensure the move is vertical
    // Need to check separate magnitudes for the colours to make sure it is only moving forward
    if (targetPosition->isPositionFree() && fromFile == toFile)
    {
        // If it is the first move, check the move is 2 squares max and square it passes through is free
        if (thisPiece->isFirstMove && thisPiece->isPathClear(fromRank, fromFile, toRank, toFile, cb))
        {
            if (thisPiece->getColour() == 'W')
            {
                if (toRank == fromRank + 2)
                    return true;
            }
            else
            {
                if (toRank == fromRank - 2)
                    return true;
            }
        }

        // If it was only a magnitude of one, it doesn't matter if first move or not - check the move is only 1 square in magnitude
        if (thisPiece->getColour() == 'W')
        {
            if ((toRank == fromRank + 1))
                return true;
        }
        else
        {
            if ((toRank == fromRank - 1))
                return true;
        }
    }

    // If the target position has the other player
    else if (!targetPosition->isPositionFree())
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
