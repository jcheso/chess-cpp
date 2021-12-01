#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
class ChessBoard;
#include "ChessBoard.h"
#include <string>
#include <vector>

// TODO - Store the rank & file of each chess piece inside it so we can getCoords
class ChessPiece
{
private:
    int colour;
    std::string name;
    int rank, file;

protected:
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

public:
    // ** Constructor, Destructor **
    ChessPiece(int colour, std::string name, int rank, int file);
    virtual ~ChessPiece();

    // ** GETTERS **
    bool canTakePiece(int rank, int file, int rankToCheck, int fileToCheck, ChessBoard *cb);
    int getColour();
    std::string getName();
    std::vector<std::string> getMoveDirection(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    bool isPositionFree();
    bool hasValidMove(int rankFrom, int fileFrom, int &rankTo, int &fileTo, ChessBoard *cb);
    bool isValidMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    bool isPathClear(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    bool freeSquaresHorizontal(int fromRank, int fromFile, int toRank, int toFile, std::string fileDirection, ChessBoard *cb);
    bool freeSquaresVertical(int fromRank, int fromFile, int toRank, int toFile, std::string rankDirection, ChessBoard *cb);
    bool freeSquaresDiagonal(int fromRank, int fromFile, int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb);
};

#endif
