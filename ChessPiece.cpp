#include "ChessPiece.hpp"
#include <iostream>
#include <string>
#include <vector>

// ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
ChessPiece::ChessPiece(char colour, std::string name) : colour(colour), name(name) {}
ChessPiece::~ChessPiece() {}

// ** GETTERS **
char ChessPiece::getColour() { return this->colour; }
std::string ChessPiece::getName() { return this->name; }
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
        return this->freeSquaresHorizontal(fromRank, fromFile, toRank, toFile, pathDetails, cb);

    if (pathDetails[0] == "Vertical")
        return this->freeSquaresVertical(fromRank, fromFile, toRank, toFile, pathDetails, cb);

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
        fileDirection = "Left";
    else if (fromFile - toFile > 0)
        fileDirection = "Right";
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

int ChessPiece::freeSquaresHorizontal(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb)
{
    int count = 0;
    std::string fileDirection = pathDetails[1];

    // If the file direction is up, we want to count the squares above the target location
    if (fileDirection == "Up")
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank, fromFile + 1)->getName() == "Free" && fromFile < toFile)
        {
            fromFile++;
            count++;
        }
    }
    else
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank, fromFile - 1)->getName() == "Free" && fromFile > toFile)
        {
            fromFile--;
            count--;
        }
    }
    return count;
}

int ChessPiece::freeSquaresVertical(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb)
{
    int count = 0;
    if (colour == 'W')
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank + 1, fromFile)->getName() == "Free" && fromRank < toRank)
        {
            fromRank++;
            count++;
        }
    }
    else
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank - 1, fromFile)->getName() == "Free" && fromRank > toRank)
        {
            fromRank--;
            count--;
        }
    }
    return count;
}

int ChessPiece::freeSquaresDiagonal(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb)
{
    int count = 0;
    if (colour == 'W')
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank + 1, fromFile + 1)->getName() == "Free" && fromRank < toRank)
        {
            fromRank++;
            fromFile++;
            count++;
        }
    }
    else
    {
        // While there empty squares, count the max free path to travel
        while (cb->getChessPiece(fromRank - 1, fromFile - 1)->getName() == "Free" && fromRank > toRank)
        {
            fromRank--;
            count--;
        }
    }
    return count;
}
