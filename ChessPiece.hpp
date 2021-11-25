#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP
class ChessBoard;
#include "ChessBoard.hpp"
#include <string>
#include <vector>

class ChessPiece
{
private:
    // Check if the move is legal for the specific piece
    char colour;
    std::string name;

protected:
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

public:
    // ** Constructor, Destructor, Copy Constructor, Equals Assignment Overload **
    ChessPiece(char colour, std::string name);
    ~ChessPiece();

    bool isFirstMove = true;
    // ** GETTERS **
    // Get the name of the piece
    std::string getName();
    // Get the colour of the piece
    char getColour();
    // Get the direction of the move
    std::vector<std::string> getMoveDirection(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    // Check the move path is clear
    bool isPathClear(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    // Get the number of empty squares in each direction
    bool freeSquaresHorizontal(int fromRank, int fromFile, int toRank, int toFile, std::string fileDirection, ChessBoard *cb);
    bool freeSquaresVertical(int fromRank, int fromFile, int toRank, int toFile, std::string rankDirection, ChessBoard *cb);
    bool freeSquaresDiagonal(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb);
    // Check if the move is valid (i.e. empty spot and not the same colour) and call isLegalMove()
    bool isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    bool isPositionFree();
};

#endif
