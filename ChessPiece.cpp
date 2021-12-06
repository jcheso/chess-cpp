#include "ChessPiece.h"

#include <iostream>
#include <string>
#include <vector>

#include "Helper.h"

// ** Constructor, Destructor **
ChessPiece::ChessPiece(int colour, std::string name, int rank, int file) : colour(colour), name(name), currentRank(rank), currentFile(file) {}
ChessPiece::~ChessPiece() {}
bool ChessPiece::isLegalMove(int toRank, int toFile, ChessBoard *cb) { return false; }

// ** SETTERS **

void ChessPiece::updatePosition(int rank, int file) {
    currentRank = rank;
    currentFile = file;
}

// ** GETTERS **

int ChessPiece::getColour() { return colour; }

std::string ChessPiece::getName() { return name; }

// TODO: Store these as ints with Enum
std::vector<std::string> ChessPiece::getMoveDirection(int toRank, int toFile) {
    std::vector<std::string> pathDetails;
    std::string direction;
    std::string fileDirection;
    std::string rankDirection;

    // Check if the move is up or down the board
    if (currentRank - toRank < 0)
        rankDirection = "Up";
    else if (currentRank - toRank > 0)
        rankDirection = "Down";
    else
        rankDirection = "No Change";

    // Check if the move is left or right across the board
    if (currentFile - toFile < 0)
        fileDirection = "Right";
    else if (currentFile - toFile > 0)
        fileDirection = "Left";
    else
        fileDirection = "No Change";

    // Check if it is a horizontal, vertical or diagonal move
    if (rankDirection == "No Change" && fileDirection != "No Change")
        direction = "Horizontal";
    else if (fileDirection == "No Change" && rankDirection != "No Change")
        direction = "Vertical";
    else
        direction = "Diagonal";

    pathDetails.push_back(direction);
    pathDetails.push_back(fileDirection);
    pathDetails.push_back(rankDirection);

    return pathDetails;
}

bool ChessPiece::isPositionFree() {
    if (getName() == "Free")
        return true;
    else
        return false;
}

bool ChessPiece::hasValidMove(int &rankTo, int &fileTo, ChessBoard *cb) {
    for (rankTo = RANK_8; rankTo >= RANK_1; rankTo--) {
        for (fileTo = FILE_A; fileTo <= FILE_H; fileTo++) {
            if (isMoveValid(currentRank, currentFile, rankTo, fileTo, cb))
                return true;
        }
    }
    return false;
}

// TODO Need to make sure the player hasn't put themselves in check or checkmate?
bool ChessPiece::isMoveValid(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) {
    ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);
    // If the position is the opposite player or is empty (i.e. not the players piece), check if the move is valid for the specific piece
    if (colour != targetPosition->getColour())
        return isLegalMove(toRank, toFile, cb);
    else
        return false;
}

bool ChessPiece::isPathClear(int toRank, int toFile, ChessBoard *cb) {
    // Get the details of the move and check the corresponding path is free
    std::vector<std::string> pathDetails;
    pathDetails = getMoveDirection(toRank, toFile);
    if (pathDetails[0] == "Diagonal")
        return isDiagonalPathClear(toRank, toFile, pathDetails, cb);

    if (pathDetails[0] == "Horizontal")
        return isHorizontalPathClear(toRank, toFile, pathDetails[1], cb);

    if (pathDetails[0] == "Vertical")
        return isVerticalPathClear(toRank, toFile, pathDetails[2], cb);

    return false;
}

bool ChessPiece::isHorizontalPathClear(int toRank, int toFile, std::string fileDirection, ChessBoard *cb) {
    // If the file direction is up, we want to count the squares above the target location
    if (fileDirection == "Right") {
        for (int filePath = currentFile + 1; filePath < toFile; filePath++) {
            if (!cb->getChessPiece(currentRank, filePath)->isPositionFree())
                return false;
        }
    } else {
        // While there empty squares, count the max free path to travel
        for (int filePath = currentFile - 1; filePath > toFile; filePath--) {
            if (!cb->getChessPiece(currentRank, filePath)->isPositionFree())
                return false;
        }
    }
    return true;
}

bool ChessPiece::isVerticalPathClear(int toRank, int toFile, std::string rankDirection, ChessBoard *cb) {
    // If the file direction is up, we want to count the squares above the target location
    if (rankDirection == "Up") {
        for (int rankPath = currentRank + 1; rankPath < toRank; rankPath++) {
            if (!cb->getChessPiece(rankPath, currentFile)->isPositionFree())
                return false;
        }
    } else {
        // While there empty squares, count the max free path to travel
        for (int rankPath = currentRank - 1; rankPath > toRank; rankPath--) {
            if (!cb->getChessPiece(rankPath, currentFile)->isPositionFree())
                return false;
        }
    }
    return true;
}

bool ChessPiece::isDiagonalPathClear(int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb) {
    std::string fileDirection = pathDetails[1];
    std::string rankDirection = pathDetails[2];

    // Check if diagonal is even
    if ((abs(currentRank - toRank) != abs(currentFile - toFile)))
        return false;

    // If the file direction is up, we want to count the squares above the target location
    if (rankDirection == "Up" && fileDirection == "Right") {
        int rankPath = currentRank + 1;
        for (int filePath = currentFile + 1; filePath < toFile && rankPath < toRank; filePath++) {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath++;
        }
    } else if (rankDirection == "Down" && fileDirection == "Left") {
        int rankPath = currentRank - 1;
        for (int filePath = currentFile - 1; filePath > toFile && rankPath > toRank; filePath--) {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath--;
        }
    } else if (rankDirection == "Down" && fileDirection == "Right") {
        int rankPath = currentRank - 1;
        for (int filePath = currentFile + 1; filePath < toFile && rankPath > toRank; filePath++) {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath--;
        }
    } else if (rankDirection == "Up" && fileDirection == "Left") {
        int rankPath = currentRank + 1;
        for (int filePath = currentFile - 1; filePath > toFile && rankPath < toRank; filePath--) {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath++;
        }
    }

    return true;
}
