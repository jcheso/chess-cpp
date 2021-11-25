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
#include <iomanip>
bool ChessBoard::isStalemate() { return false; }
void ChessBoard::clearBoard()
{
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            delete this->getChessPiece(rank, file);
        }
    }
}
void ChessBoard::setBoard()
{
    // Fill the board with Black Pieces
    for (int file = F_A; file <= F_H; file++)
        board[R_7][file] = new Pawn('B', "Pawn");

    board[R_8][F_A] = new Rook('B', "Rook");
    board[R_8][F_B] = new Knight('B', "Knight");
    board[R_8][F_C] = new Bishop('B', "Bishop");
    board[R_8][F_D] = new Queen('B', "Queen");
    board[R_8][F_E] = new King('B', "King");
    board[R_8][F_F] = new Bishop('B', "Bishop");
    board[R_8][F_G] = new Knight('B', "Knight");
    board[R_8][F_H] = new Rook('B', "Rook");

    // Fill the board with White Pieces
    for (int file = F_A; file <= F_H; file++)
        board[R_2][file] = new Pawn('W', "Pawn");

    board[R_1][F_A] = new Rook('W', "Rook");
    board[R_1][F_B] = new Knight('W', "Knight");
    board[R_1][F_C] = new Bishop('W', "Bishop");
    board[R_1][F_D] = new Queen('W', "Queen");
    board[R_1][F_E] = new King('W', "King");
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

void ChessBoard::resetGame()
{
    clearBoard();
    setBoard();
}

void ChessBoard::printBoard()
{
    std::cout
        << "\n"
        << "|----------------------------------------------------------------------------------|" << std::endl;
    if (this->isWhiteTurn)
    {
        std::cout << std::setw(20) << "|                            **White's turn to move!**                             |" << std::endl;
    }
    else
    {
        std::cout << std::setw(20) << "|                            **Black's turn to move!**                             |" << std::endl;
    }
    std::cout
        << "|----------------------------------------------------------------------------------|" << std::endl;
    std::cout << std::setw(2) << "|     ";
    std::cout << "|   A  |  |  B   |  |  C   |  |  D   |  |  E   |  |  F   |  |  G   |  |  H   |" << std::endl;
    std::cout
        << "|----------------------------------------------------------------------------------|" << std::endl;
    // std::cout << std::setw(2) << " | "
    for (int rank = R_8; rank >= R_1; rank--)
    {
        std::cout << std::setw(3);
        std::cout << "|  " << rank + 1 << " ";
        for (int file = F_A; file <= F_H; file++)
        {
            if (this->getChessPiece(rank, file)->getName() != "Free")
            {
                std::cout << std::setw(2) << " | ";
                std::cout << this->getChessPiece(rank, file)->getColour() << "_" << this->getChessPiece(rank, file)->getName()[0] << this->getChessPiece(rank, file)->getName()[1];
                std::cout << std::setw(2) << " | ";
            }
            else
            {
                std::cout << std::setw(2) << " | ";
                std::cout << std::setw(7) << " | ";
            }
        }
        std::cout << "\n"
                  << "|----------------------------------------------------------------------------------|" << std::endl;
    }
}
ChessBoard::ChessBoard() { setBoard(); }

ChessBoard::~ChessBoard()
{
    // Call clearBoard()
}
ChessPiece *ChessBoard::getChessPiece(int rank, int file) { return this->board[rank][file]; }

bool ChessBoard::submitMove(std::string moveFrom, std::string moveTo)
{
    // TODO - Move these shared functions to the helper class
    // Parse the input strings into two sets of coordinates
    int fromRank = moveFrom[1] - 1 - '0';
    int fromFile = moveFrom[0] - 'A';
    int toRank = moveTo[1] - 1 - '0';
    int toFile = moveTo[0] - 'A';

    // Check if it is a valid board position
    if (!((fromRank >= R_1 && fromRank <= R_8) && (fromFile <= 'A' && fromFile <= 'G')) && ((toRank >= R_1 && toRank <= R_8) && (toFile <= 'A' && toFile <= 'G')))
    {
        std::cerr << "Not a valid board position!" << std::endl;
        return false;
    }

    // Get the piece at that position
    ChessPiece *pieceToMove = this->getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = this->getChessPiece(toRank, toFile);
    // Check if there is a piece at the position
    if (pieceToMove->isPositionFree())
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
    if (!isWhiteTurn && pieceToMove->getColour() == 'W')
    {
        std::cout << "It is not White's turn to move!" << std::endl;
        return false;
    }

    // Then check if the move is valid
    if (!this->getChessPiece(fromRank, fromFile)->isValidMove(fromRank, fromFile, toRank, toFile, this))
    {
        // If not valid
        if (isWhiteTurn)
            std::cout << "White's " << this->getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;
        else
            std::cout << "Blacks's " << this->getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;

        return false;
    }

    // Print the move to console
    if (isWhiteTurn)
    {
        std::cout << "White's " << this->getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking Black's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        isWhiteTurn = false;
    }
    else
    {
        std::cout << "Black's " << this->getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;

        if (!targetPosition->isPositionFree())
            std::cout << " taking White's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        isWhiteTurn = true;
    }

    // ? Keep a 2D set of possible moves and just check if this move is in there, then recalculate each turn for every piece?
    // ? This way we can check for checkmate and also check for stalemate - i.e. set contains king coordinates or set is empty.
    // Make the move, set target to piece and original position to free
    this->board[toRank][toFile] = pieceToMove;
    pieceToMove->isFirstMove = false;
    this->board[fromRank][fromFile] = new ChessPiece('.', "Free");

    return true;
}