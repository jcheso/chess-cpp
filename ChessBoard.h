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
    bool whiteInCheck, blackInCheck, checkmate, stalemate;

    // ** GETTERS **

    /* Check if it is white's turn */
    bool isWhiteTurn();
    /* This method finds the rank and file of the King for the current player */
    void getKingCoordinates(int &kingRank, int &kingFile);
    /* This method checks if the piece at rank and file passed in can be taken by the opposite team */
    bool pieceCanBeTaken(int rankToCheck, int fileToCheck);
    /* This method checks if current player is in Check */
    bool isCheck();
    /* This method checks if current player is in Checkmate */
    bool isCheckmate();
    /* This method checks if a piece can interpose the check */
    bool canInterposeCheck();
    /* This method checks if a piece that can block an attack */
    bool pieceCanBlockAttack(int rankFrom, int fileFrom);
    /* This method checks if the King can move out of the check position */
    bool canKingMoveOutOfCheck(int kingRank, int kingFile);
    /* This method checks if the attacking piece causing check can be captured */
    bool canCaptureAttackingPiece(int kingRank, int kingFile);
    /* This method checks if there is a Stalemate */
    bool isStalemate();
    /* This method checks for check, checkmate, stalemate */
    void checkGameStatus();
    /* This method checks if the player is moving it's own piece */
    bool isPlayersTurn(ChessPiece *pieceToMove);
    /* This method validates the move, ensuring the game hasn't ended, that it's the players turn,
    that they are selecting their own piece, and that the piece is making a valid move */
    bool moveNotValid(ChessPiece *pieceToMove, std::string moveFrom, std::string moveTo, int toRank, int toFile);

    // ** SETTERS **

    /* This method sets the board for a new game */
    void setBoard();
    /* This method deletes all the objects on the board from memory */
    void clearBoard();
    /* This method handles the required input validation and move validation */
    bool parseInput(std::string moveFrom, std::string moveTo, int &fromRank, int &fromFile, int &toRank, int &toFile);
    /* This method swaps the players turn */
    void swapTurn();
    /* This method makes sure that the player is not checking themself and sets the ChessBoard if the move is valid */
    bool causingSelfCheck(int fromRank, int fromFile, int toRank, int toFile, std::string moveTo);
    // ** HELPERS **
    /* This method prints the move to the console */
    void printMove(ChessPiece *targetPosition, ChessPiece *originalPosition, std::string moveFrom, std::string moveTo);

   public:
    ChessBoard();
    ~ChessBoard();

    // ** VARIABLES **
    int currentPlayer, oppositionPlayer;

    // ** GETTERS **

    /* This method returns the ChessPiece object at the rank and file */
    ChessPiece *getChessPiece(int rank, int file);

    // ** SETTERS **

    /* This method submits a move to the chessboard for further validation */
    bool submitMove(std::string moveFrom, std::string moveTo);
    /* This method resets the board in preparation for a new game */
    void resetBoard();
};

#endif
