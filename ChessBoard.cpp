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

ChessBoard::ChessBoard() { setBoard(); }
ChessBoard::~ChessBoard() { clearBoard(); }

bool ChessBoard::isStalemate()
{
    // check who's turn it is
    // iterate through all their pieces and see if there is a valid move
    // if there is a valid move, make sure the king isn't in check after
    // else it is a stalemate

    char thisTeam;
    char oppositeTeam;
    int kingRank;
    int kingFile;
    int pieceCount = 0;
    int attackingPieceRank;
    int attackingPieceFile;

    if (this->isWhiteTurn)
    {
        thisTeam = 'W';
        oppositeTeam = 'B';
    }
    else
    {
        thisTeam = 'B';
        oppositeTeam = 'W';
    }

    getKingCoordinates(kingRank, kingFile, thisTeam);

    return false;
}

bool ChessBoard::isCheckmate()
{
    // TODO: Refactor this into a function
    char thisTeam;
    char oppositeTeam;
    int kingRank;
    int kingFile;
    int pieceCount = 0;
    int attackingPieceRank;
    int attackingPieceFile;

    if (this->isWhiteTurn)
    {
        thisTeam = 'W';
        oppositeTeam = 'B';
    }
    else
    {
        thisTeam = 'B';
        oppositeTeam = 'W';
    }

    getKingCoordinates(kingRank, kingFile, thisTeam);

    ChessPiece *king = this->getChessPiece(kingRank, kingFile);

    // King is in check, see if it can move somewhere which avoids the check
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            // Check if it can move somewhere, then check if it is still in check in that move - repeat for all possible moves
            if ((king->isValidMove(kingRank, kingFile, rank, file, this)) && !(this->isKingInCheck(rank, file, oppositeTeam)))
                return false;
        }
    }

    // Check how many pieces can take the King, if it is more than 1 return true to checkmate => in checkmate
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            if (this->getChessPiece(rank, file)->getColour() == oppositeTeam && this->getChessPiece(rank, file)->isValidMove(rank, file, kingRank, kingFile, this))
            {
                attackingPieceFile = file;
                attackingPieceRank = rank;
                pieceCount++;
                if (pieceCount > 1)
                {
                    return true;
                }
            }
        }
    }

    // If only one piece can take it, check if the player in Check can take that piece with a valid move. Return false if it can => not in Checkmate
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            if (this->getChessPiece(rank, file)->getColour() == thisTeam && this->getChessPiece(rank, file)->isValidMove(rank, file, attackingPieceRank, attackingPieceFile, this))
                return false;
        }
    }

    return true;
}

void ChessBoard::getKingCoordinates(int &kingRank, int &kingFile, char colour)
{
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            if (this->getChessPiece(rank, file)->getName() == "King" && this->getChessPiece(rank, file)->getColour() == colour)
            {
                kingRank = rank;
                kingFile = file;
            }
        }
    }
}

bool ChessBoard::isCheck()
{

    char colourToCheck;
    char oppositeTeam;
    int kingToCheckRank;
    int kingToCheckFile;

    // Check if it is white or black turn and set targets accordingly
    if (this->isWhiteTurn)
    {
        colourToCheck = 'W';
        oppositeTeam = 'B';
    }
    else
    {
        colourToCheck = 'B';
        oppositeTeam = 'W';
    }

    // Get the coordinates of the King to find out if it is in check
    getKingCoordinates(kingToCheckRank, kingToCheckFile, colourToCheck);

    // Check if the King can be taken, if so return true for king in check
    if (this->isKingInCheck(kingToCheckRank, kingToCheckFile, oppositeTeam))
        return true;

    return false;
}

bool ChessBoard::isKingInCheck(int rankToCheck, int fileToCheck, char oppositeTeam)
{
    // Iterate through every position on the board, if it is the oppositeTeams piece see if it can take the King
    // If the piece can take it, check if the player in Check can take that piece with a valid move (can only do this if just 1 piece causing the check)
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
        {
            if (this->getChessPiece(rank, file)->getColour() == oppositeTeam && this->getChessPiece(rank, file)->isValidMove(rank, file, rankToCheck, fileToCheck, this))
                return true;
        }
    }
    return false;
}

void ChessBoard::clearBoard()
{
    for (int rank = R_8; rank >= R_1; rank--)
    {
        for (int file = F_A; file <= F_H; file++)
            delete this->getChessPiece(rank, file);
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
    // Set white's turn
    isWhiteTurn = true;
}

void ChessBoard::resetBoard()
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

ChessPiece *ChessBoard::getChessPiece(int rank, int file) { return this->board[rank][file]; }

bool ChessBoard::submitMove(std::string moveFrom, std::string moveTo)
{
    // TODO - Split up into smaller functions
    // ? Consider storing the from/to in the object itself as variables, so we can access them everywhere instead of passing them around

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

    if (isWhiteTurn && isCheck())
    {
        if (isCheckmate())
            std::cout << "White is in checkmate" << std::endl;
        else
            std::cout << "White is in check" << std::endl;
    }
    else if (!isWhiteTurn && isCheck())
    {
        if (isCheckmate())
            std::cout << "Black is in checkmate" << std::endl;
        else
            std::cout << "Black is in check" << std::endl;
    }
    // else if (!isCheck() && isCheckmate())
    // {

    //     std::cout << "A stalemate has occured" << std::endl;
    // }

    return true;
}