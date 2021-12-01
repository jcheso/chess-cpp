#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
class ChessPiece;
#include "ChessPiece.h"
#include <string>
#include "Helper.h"

class ChessBoard
{
private:
    // ** VARIABLES **
    ChessPiece *board[8][8];

    // ** GETTERS **
    bool isWhiteTurn();
    /* This method sets the rank and file of the King for the colour passed in */
    void getKingCoordinates(int &kingRank, int &kingFile, int colour);
    /* This method checks if the piece at rank and file passed in can be taken by the opposite team */
    bool pieceCanBeTaken(int rankToCheck, int fileToCheck, int oppositionColour);
    /* This method checks if current player is in Check */
    bool isCheck();
    /* This method checks if current player is in Checkmate */
    bool isCheckmate();
    /* This method checks if there is a Stalemate */
    bool isStalemate();

    // ** SETTERS **

    /* This method sets the board for a new game */
    void setBoard();
    /* This method deletes all the objects on the board from memory */
    void clearBoard();

public:
    ChessBoard();
    ~ChessBoard();

    // ** VARIABLES **
    int currentPlayer;
    int oppositionPlayer;

    // ** GETTERS **

    /* This method returns the ChessPiece object at the rank and file */
    ChessPiece *getChessPiece(int rank, int file);
    /* This method prints the current state of the game to the console */
    void printBoard();

    // ** SETTERS **

    /* This method submits a move to the chessboard for further validation */
    bool submitMove(std::string moveFrom, std::string moveTo);
    /* This method resets the board in preparation for a new game */
    void resetBoard();
};

#endif
