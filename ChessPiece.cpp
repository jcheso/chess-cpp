#include "ChessPiece.h"
#include "Helper.h"
#include <iostream>
#include <string>
#include <vector>

// ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
ChessPiece::ChessPiece(char colour, std::string name) : colour(colour), name(name) {}
ChessPiece::~ChessPiece() {}

// ** GETTERS **
bool ChessPiece::isPositionFree()
{
    if (this->getName() == "Free")
        return true;
    else
        return false;
}

int ChessPiece::getColour() { return this->colour; }

std::string ChessPiece::getName() { return this->name; }

bool ChessPiece::hasValidMove(int rankFrom, int fileFrom, int &rankTo, int &fileTo, ChessBoard *cb)
{
    for (rankTo = RANK_8; rankTo >= RANK_1; rankTo--)
    {
        for (fileTo = FILE_A; fileTo <= FILE_H; fileTo++)
        {
            if (this->isValidMove(rankFrom, fileFrom, rankTo, fileTo, cb))
                return true;
        }
    }
    return false;
}

bool ChessPiece::isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb) { return false; }

bool ChessPiece::isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // Create a pointer to the piece(or empty spot) on the board
    ChessPiece *targetPosition = cb->getChessPiece(toRank, toFile);
    // If the position is the opposite player or is empty (i.e. not the players piece), check if the move is valid for the specific piece
    if (this->colour != targetPosition->getColour())
        return isLegalMove(fromRank, fromFile, toRank, toFile, cb);
    else
        return false;
}

bool ChessPiece::isPathClear(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    // Get the move type (horizontal, vertical or diagonal) and directionX & directionY
    std::vector<std::string> pathDetails;
    pathDetails = this->getMoveDirection(fromRank, fromFile, toRank, toFile, cb);

    if (pathDetails[0] == "Diagonal")
        return this->freeSquaresDiagonal(fromRank, fromFile, toRank, toFile, pathDetails, cb);

    if (pathDetails[0] == "Horizontal")
        return this->freeSquaresHorizontal(fromRank, fromFile, toRank, toFile, pathDetails[1], cb);

    if (pathDetails[0] == "Vertical")
        return this->freeSquaresVertical(fromRank, fromFile, toRank, toFile, pathDetails[2], cb);

    return false;
}

std::vector<std::string> ChessPiece::getMoveDirection(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb)
{
    std::vector<std::string> pathDetails;
    std::string type;
    std::string fileDirection;
    std::string rankDirection;

    // Check if the move is up or down the board
    if (fromRank - toRank < 0)
        rankDirection = "Up";
    else if (fromRank - toRank > 0)
        rankDirection = "Down";
    else
        rankDirection = "No Change";

    // Check if the move is left or right across the board
    if (fromFile - toFile < 0)
        fileDirection = "Right";
    else if (fromFile - toFile > 0)
        fileDirection = "Left";
    else
        fileDirection = "No Change";

    // Check if it solely horizontal, vertical or diagonal
    if (rankDirection == "No Change" && fileDirection != "No Change")
        type = "Horizontal";
    else if (fileDirection == "No Change" && rankDirection != "No Change")
        type = "Vertical";
    else
        type = "Diagonal";

    pathDetails.push_back(type);
    pathDetails.push_back(fileDirection);
    pathDetails.push_back(rankDirection);

    return pathDetails;
}

bool ChessPiece::freeSquaresHorizontal(int fromRank, int fromFile, int toRank, int toFile, std::string fileDirection, ChessBoard *cb)
{
    // If the file direction is up, we want to count the squares above the target location
    if (fileDirection == "Right")
    {
        for (int filePath = fromFile + 1; filePath < toFile; filePath++)
        {
            if (!cb->getChessPiece(fromRank, filePath)->isPositionFree())
                return false;
        }
    }
    else
    {
        // While there empty squares, count the max free path to travel
        for (int filePath = fromFile - 1; filePath > toFile; filePath--)
        {
            if (!cb->getChessPiece(fromRank, filePath)->isPositionFree())
                return false;
        }
    }
    return true;
}

bool ChessPiece::freeSquaresVertical(int fromRank, int fromFile, int toRank, int toFile, std::string rankDirection, ChessBoard *cb)
{
    // If the file direction is up, we want to count the squares above the target location
    if (rankDirection == "Up")
    {
        for (int rankPath = fromRank + 1; rankPath < toRank; rankPath++)
        {
            if (!cb->getChessPiece(rankPath, fromFile)->isPositionFree())
                return false;
        }
    }
    else
    {
        // While there empty squares, count the max free path to travel
        for (int rankPath = fromRank - 1; rankPath > toRank; rankPath--)
        {
            if (!cb->getChessPiece(rankPath, fromFile)->isPositionFree())
                return false;
        }
    }
    return true;
}

bool ChessPiece::freeSquaresDiagonal(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb)
{
    std::string fileDirection = pathDetails[1];
    std::string rankDirection = pathDetails[2];

    // Check if diagonal is even
    if ((abs(fromRank - toRank) != abs(fromFile - toFile)))
        return false;

    // If the file direction is up, we want to count the squares above the target location
    if (rankDirection == "Up" && fileDirection == "Right")
    {
        int rankPath = fromRank + 1;
        for (int filePath = fromFile + 1; filePath < toFile && rankPath < toRank; filePath++)
        {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath++;
        }
    }
    else if (rankDirection == "Down" && fileDirection == "Left")
    {
        int rankPath = fromRank - 1;
        for (int filePath = fromFile - 1; filePath > toFile && rankPath > toRank; filePath--)
        {

            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath--;
        }
    }
    else if (rankDirection == "Down" && fileDirection == "Right")
    {
        int rankPath = fromRank - 1;
        for (int filePath = fromFile + 1; filePath < toFile && rankPath > toRank; filePath++)
        {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath--;
        }
    }
    else if (rankDirection == "Up" && fileDirection == "Left")
    {
        int rankPath = fromRank + 1;
        for (int filePath = fromFile - 1; filePath > toFile && rankPath < toRank; filePath--)
        {
            if (!cb->getChessPiece(rankPath, filePath)->isPositionFree())
                return false;

            rankPath++;
        }
    }

    return true;
}
