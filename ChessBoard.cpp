#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Helper.hpp"
#include <string>
#include <iostream>

bool ChessBoard::isStalemate() { return false; }
void ChessBoard::resetGame() {}
void ChessBoard::printBoard() {}
ChessBoard::ChessBoard()
{
    // Fill the board with Black Pieces
    for (int file = F_A; file <= F_H; file++)
        board[R_7][file] = new Pawn('B', "Pawn");

    board[R_8][F_A] = new Rook('B', "Rook");
    board[R_8][F_B] = new Knight('B', "Knight");
    board[R_8][F_C] = new Bishop('B', "Bishop");
    board[R_8][F_D] = new King('B', "King");
    board[R_8][F_E] = new Queen('B', "Queen");
    board[R_8][F_F] = new Bishop('B', "Bishop");
    board[R_8][F_G] = new Knight('B', "Knight");
    board[R_8][F_H] = new Rook('B', "Rook");

    // Fill the board with White Pieces
    for (int file = F_A; file <= F_H; file++)
        board[R_2][file] = new Pawn('W', "Pawn");

    board[R_1][F_A] = new Rook('W', "Rook");
    board[R_1][F_B] = new Knight('W', "Knight");
    board[R_1][F_C] = new Bishop('W', "Bishop");
    board[R_1][F_D] = new King('W', "King");
    board[R_1][F_E] = new Queen('W', "Queen");
    board[R_1][F_F] = new Bishop('W', "Bishop");
    board[R_1][F_G] = new Knight('W', "Knight");
    board[R_1][F_H] = new Rook('W', "Rook");

    // Fill the remainder of the board with nullptr
    for (int rank = R_3; rank <= R_6; rank++)
    {
        for (int file = F_A; file <= F_H; file++)
            board[rank][file] = new ChessPiece('.', "Free");
    }
    std::cout << "A new chess game is started!" << std::endl;
}
ChessBoard::~ChessBoard() {}
ChessPiece *ChessBoard::getChessPiece(int rank, int file) { return this->board[rank][file]; }
bool ChessBoard::submitMove(std::string moveFrom, std::string moveTo)
{

    // Parse the input strings into two sets of coordinates
    int rankFrom = moveFrom[1] - 1 - '0';
    int fileFrom = moveFrom[0] - 'A';
    int rankTo = moveTo[1] - 1 - '0';
    int fileTo = moveTo[0] - 'A';

    // Check if it is a valid board position - put this in a function?
    if (!((R_1 <= rankFrom <= R_8) && ('A' <= fileFrom <= 'G')) && ((R_1 <= rankTo <= R_8) && ('A' <= fileTo <= 'G')))
    {
        std::cerr << "Not a valid board position!" << std::endl;
        return false;
    }

    // Get the piece at that position
    ChessPiece *pieceToMove = this->getChessPiece(rankFrom, fileFrom);

    // Check if there is a piece at the position
    if (pieceToMove->getName() == "Free")
    {
        std::cout << "There is no piece at position " << moveFrom << "!" << std::endl;
        return false;
    }

    // Check if the piece belongs to the player who's turn it is.
    if (isWhiteTurn && pieceToMove->getColour() == 'B')
    {
        std::cout << "It is not Black's turn to move!" << std::endl;
        return false;
    }
    else if (!isWhiteTurn && pieceToMove->getColour() == 'W')
    {
        std::cout << "It is not White's turn to move!" << std::endl;
        return false;
    }

    // Then check if the move is valid

    // Print the move to console
    if (isWhiteTurn)
    {
        std::cout << "White's " << this->getChessPiece(rankFrom, fileFrom)->getName() << " moves from "
                  << moveFrom << " to " << moveTo << std::endl;
        isWhiteTurn = false;
    }
    else
    {
        std::cout << "Black's " << this->getChessPiece(rankFrom, fileFrom)->getName() << " moves from "
                  << moveFrom << " to " << moveTo << std::endl;
        isWhiteTurn = true;
    }
}