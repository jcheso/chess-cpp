#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
class ChessBoard;
#include <string>
#include <vector>

#include "ChessBoard.h"

class ChessPiece {
   private:
    /* An integer represents a colour to prevent an unnecessary string comparison */
    int colour;
    /* A string name is used for each piece for comparisons and for printing to console */
    std::string name;

   protected:
    /* This method checks if the submitted move is legal */
    virtual bool isLegalMove(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);

   public:
    /* These variables hold the pieces position on the board */
    int currentRank, currentFile;

    // ** Constructor, Destructor **
    ChessPiece(int colour, std::string name, int rank, int file);
    virtual ~ChessPiece();

    // ** SETTERS **

    /* This method updates the current rank and file of a piece so it knows where it is on the board */
    void updatePosition(int rank, int file);

    // ** GETTERS **

    /* This method returns the colour of the piece */
    int getColour();
    /* This method returns the name of the piece */
    std::string getName();
    /* This method returns the direction of move (Up/Down, Left/Right, Diagonal/Horizontal/Vertical) */
    std::vector<std::string> getMoveDirection(int toRank, int toFile);
    /* This method checks if it is a free piece */
    bool isPositionFree();
    /* This method checks if the piece has a valid move available on the board */
    bool hasValidMove(int &toRank, int &toFile, ChessBoard *cb);
    /* This method checks if the piece can make a the specific move on the board */
    bool isMoveValid(int fromRank, int fromFile, int toRank, int toFile, ChessBoard *cb);
    /* This method checks if the piece has a clear path to the desired position on the board */
    bool isPathClear(int toRank, int toFile, ChessBoard *cb);
    /* This method checks if a horizontal path is clear to the desired position on the board */
    bool isHorizontalPathClear(int toRank, int toFile, std::string fileDirection, ChessBoard *cb);
    /* This method checks if a vertical path is clear to the desired position on the board */
    bool isVerticalPathClear(int toRank, int toFile, std::string rankDirection, ChessBoard *cb);
    /* This method checks if a diagonal path is clear to the desired position on the board */
    bool isDiagonalPathClear(int toRank, int toFile, std::vector<std::string> pathDetails, ChessBoard *cb);
};

#endif
