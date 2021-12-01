#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
class ChessBoard;
#include "ChessBoard.h"
#include <string>
#include <vector>

class ChessPiece
{
private:
    int colour;
    std::string name;

protected:
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

public:
    int currentRank, currentFile;
    // ** Constructor, Destructor **
    ChessPiece(int colour, std::string name, int rank, int file);
    virtual ~ChessPiece();
    // ** SETTERS **
    void updatePosition(int rank, int file);
    // ** GETTERS **
    int getColour();
    std::string getName();
    std::vector<std::string> getMoveDirection(int toRank, int toFile, ChessBoard *cb);
    bool isPositionFree();
    bool hasValidMove(int &toRank, int &toFile, ChessBoard *cb);
    bool isMoveValid(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    bool isPathClear(int toRank, int toFile, ChessBoard *cb);
    bool checkHorizontalPath(int toRank, int toFile, std::string fileDirection, ChessBoard *cb);
    bool checkVerticalPath(int toRank, int toFile, std::string rankDirection, ChessBoard *cb);
    bool checkDiagonalPath(int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb);
};

#endif
