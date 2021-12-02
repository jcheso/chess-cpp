#include "Pawn.h"

#include <iostream>
#include <string>

#include "ChessPiece.h"
#include "Helper.h"

Pawn::Pawn(int colour, std::string name, int rank, int file) : ChessPiece(colour, name, rank, file) {}

bool Pawn::isFirstMove() {
    if (getColour() == WHITE && currentRank == RANK_2)
        return true;
    else if (getColour() == BLACK && currentRank == RANK_7)
        return true;
    return false;
}

bool Pawn::isLegalMove(int toRank, int toFile, ChessBoard *cb) {
    ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);

    // If the target position is empty ensure the move is vertical
    // Need to check separate magnitudes for the colours to make sure it is only moving forward
    if (targetPosition->isPositionFree() && currentFile == toFile) {
        // If it is the first move, check the move is 2 squares max and square it passes through is free
        if (isFirstMove() && isPathClear(toRank, toFile, cb)) {
            if (getColour() == WHITE) {
                if (toRank == currentRank + 2)
                    return true;
            } else {
                if (toRank == currentRank - 2)
                    return true;
            }
        }

        // If it was only a magnitude of one, it doesn't matter if first move or not - check the move is only 1 square in magnitude
        if (getColour() == WHITE) {
            if ((toRank == currentRank + 1))
                return true;
        } else {
            if ((toRank == currentRank - 1))
                return true;
        }
    }

    // If the target position has the other player
    else if (!targetPosition->isPositionFree()) {
        // Check the move is diagonal by 1 file
        if ((toFile == currentFile + 1) || (toFile == currentFile - 1)) {
            // Check the move is only 1 rank in up direction for white and down for black
            if (getColour() == WHITE) {
                if (toRank == currentRank + 1)
                    return true;
            } else {
                if (toRank == currentRank - 1)
                    return true;
            }
        }
    }

    return false;
}
