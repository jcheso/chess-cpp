#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
class ChessPiece;
#include <string>

#include "ChessPiece.h"
#include "Helper.h"

class ChessBoard {
   private:
    // ** VARIABLES **
    ChessPiece *board[8][8];

    // ** GETTERS **

    /* Check if it is white's turn */
    bool isWhiteTurn();
    /* This method finds the rank and file of the King for the current player */
    void getKingCoordinates(int &kingRank, int &kingFile);
    /* This method checks if the piece at rank and file passed in can be taken by the opposite team */
    bool pieceCanBeTaken(int rankToCheck, int fileToCheck);
    /* This method checks if current player is in Check */
    bool isCheck();
    /* This method checks if a piece can interpose the check */
    bool canInterpose();
    /* This method checks if current player is in Checkmate */
    bool isCheckmate();
    /* This method checks if there is a Stalemate */
    bool isStalemate();
    /* This method checks for check, checkmate, stalemate */
    void checkGameConditions();
    /* This method checks if the player is moving it's own piece */
    bool isPlayersTurn(ChessPiece *pieceToMove);

    // ** SETTERS **

    /* This method sets the board for a new game */
    void setBoard();
    /* This method deletes all the objects on the board from memory */
    void clearBoard();
    /* This method handles the required input validation and move validation */
    bool parseInput(std::string moveFrom, std::string moveTo, int &fromRank, int &fromFile, int &toRank, int &toFile);

    // ** HELPERS **

    /* This method prints the move to the console */
    void printMove(ChessPiece *targetPosition, int fromRank, int fromFile, std::string moveFrom, std::string moveTo);

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
