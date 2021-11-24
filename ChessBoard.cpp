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
void ChessBoard::submitMove(std::string moveFrom, std::string moveTo)
{
    // Parse the input strings into two sets of coordinates
    int rankFrom = moveFrom[1] - '0';
    int fileFrom = static_cast<FileEnum>(moveFrom[0] - 'A');
    int rankTo = moveTo[1] - '0';
    int fileTo = static_cast<FileEnum>(moveTo[0] - 'A');
    // Get the piece at that position
    // Check if nullptr
    // Else if it is that piece's turn
    // Then check if the move is valid
    // Print the move to console
    if (isWhiteTurn)
    {
        std::cout << "White's" << this->getChessPiece(rankFrom, fileFrom)->getName() << "moves from "
                  << moveFrom[1] << moveFrom[2] << " to " << moveTo[1] << moveTo[2] << std::endl;
        isWhiteTurn = false;
    }
    else
    {
        std::cout << "White's" << this->getChessPiece(rankFrom, fileFrom)->getName() << "moves from "
                  << moveFrom[1] << moveFrom[2] << " to " << moveTo[1] << moveTo[2] << std::endl;
        isWhiteTurn = true;
    }
}