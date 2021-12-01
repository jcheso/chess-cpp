#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Helper.h"
#include <string>
#include <iostream>
#include <iomanip>

ChessBoard::ChessBoard() { setBoard(); }
ChessBoard::~ChessBoard() { clearBoard(); }
bool ChessBoard::isStalemate()
{
    char thisTeam;
    int rankTo, fileTo;

    if (isWhiteTurn)
        thisTeam = WHITE;
    else
        thisTeam = BLACK;

    // Test if the a piece can move somewhere where the King is not in check
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            // Check if any piece has a valid move that doesn't result in the King being checked
            if (getChessPiece(rank, file)->getColour() == thisTeam && getChessPiece(rank, file)->hasValidMove(rank, file, rankTo, fileTo, this))
            {
                ChessPiece *originalPiece = board[rankTo][fileTo];
                ChessPiece *pieceToMove = board[rank][file];
                board[rankTo][fileTo] = pieceToMove;
                board[rank][file] = new ChessPiece(NO_COLOUR, "Free", rank, file);

                // If moving the piece results in a check
                if (isCheck())
                {
                    delete getChessPiece(rank, file);
                    board[rankTo][fileTo] = originalPiece;
                    board[rank][file] = pieceToMove;
                    return true;
                }
                else
                {
                    delete getChessPiece(rank, file);
                    board[rankTo][fileTo] = originalPiece;
                    board[rank][file] = pieceToMove;
                    return false;
                }
            }
        }
    }
    return true;
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

    if (isWhiteTurn)
    {
        thisTeam = WHITE;
        oppositeTeam = BLACK;
    }
    else
    {
        thisTeam = BLACK;
        oppositeTeam = WHITE;
    }

    getKingCoordinates(kingRank, kingFile, thisTeam);

    ChessPiece *king = getChessPiece(kingRank, kingFile);

    // Test if the King can move somewhere where it's not in check
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            // Check if it can move somewhere, then check if it is still in check in that move - repeat for all possible moves
            if (king->isValidMove(kingRank, kingFile, rank, file, this))
            {
                // If the move is valid, place a temp king in that position
                ChessPiece *originalPiece = board[rank][file];
                board[rank][file] = new King(thisTeam, "King", rank, file);

                // Check if that king is in check
                if (!isKingInCheck(rank, file, oppositeTeam))
                {
                    // If the king is no longer in check, restore the original free space and return false to being in Check
                    delete getChessPiece(rank, file);
                    board[rank][file] = originalPiece;
                    return false;
                }
                // If the king is still in check regardless of the space, restore the free space and move on with the other checks.
                delete getChessPiece(rank, file);
                board[rank][file] = originalPiece;
            }
        }
    }

    // Check how many pieces can take the King, if it is more than 1 return true to checkmate => in checkmate
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            if (getChessPiece(rank, file)->getColour() == oppositeTeam && getChessPiece(rank, file)->isValidMove(rank, file, kingRank, kingFile, this))
            {
                attackingPieceFile = file;
                attackingPieceRank = rank;
                pieceCount++;
            }
        }
    }

    // If only one piece can take it, check if the player in Check can take that piece with a valid move. Return false if it can => not in Checkmate
    if (pieceCount == 1)
    {
        for (int rank = RANK_8; rank >= RANK_1; rank--)
        {
            for (int file = FILE_A; file <= FILE_H; file++)
            {
                if (getChessPiece(rank, file)->getColour() == thisTeam && getChessPiece(rank, file)->isValidMove(rank, file, attackingPieceRank, attackingPieceFile, this))
                    return false;
            }
        }
    }

    if (pieceCount < 1)
    {
        return false;
    }

    return true;
}

void ChessBoard::getKingCoordinates(int &kingRank, int &kingFile, int colour)
{
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            if (getChessPiece(rank, file)->getName() == "King" && getChessPiece(rank, file)->getColour() == colour)
            {
                kingRank = rank;
                kingFile = file;
            }
        }
    }
}

bool ChessBoard::isCheck()
{

    int colourToCheck;
    char oppositeTeam;
    int kingToCheckRank;
    int kingToCheckFile;

    // Check if it is white or black turn and set targets accordingly
    if (isWhiteTurn)
    {
        colourToCheck = WHITE;
        oppositeTeam = BLACK;
    }
    else
    {
        colourToCheck = BLACK;
        oppositeTeam = WHITE;
    }

    // Get the coordinates of the King to find out if it is in check
    getKingCoordinates(kingToCheckRank, kingToCheckFile, colourToCheck);

    // Check if the King can be taken, if so return true for king in check
    if (isKingInCheck(kingToCheckRank, kingToCheckFile, oppositeTeam))
        return true;

    return false;
}

bool ChessBoard::isKingInCheck(int rankToCheck, int fileToCheck, char oppositeTeam)
{
    // Iterate through every position on the board, if it is the oppositeTeams piece see if it can take the King
    // If the piece can take it, check if the player in Check can take that piece with a valid move (can only do this if just 1 piece causing the check)
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            // TODO: Just name the getChessPiece Ptr
            if ((getChessPiece(rank, file)->getColour() == oppositeTeam) && (getChessPiece(rank, file)->isValidMove(rank, file, rankToCheck, fileToCheck, this)))
            {
                return true;
            }
        }
    }
    return false;
}

void ChessBoard::clearBoard()
{
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
            delete board[rank][file];
    }
}

void ChessBoard::setBoard()
{
    // Fill the board with Black Pieces
    for (int file = FILE_A; file <= FILE_H; file++)
        board[RANK_7][file] = new Pawn(BLACK, "Pawn", RANK_7, file);

    board[RANK_8][FILE_A] = new Rook(BLACK, "Rook", RANK_8, FILE_A);
    board[RANK_8][FILE_B] = new Knight(BLACK, "Knight", RANK_8, FILE_B);
    board[RANK_8][FILE_C] = new Bishop(BLACK, "Bishop", RANK_8, FILE_C);
    board[RANK_8][FILE_D] = new Queen(BLACK, "Queen", RANK_8, FILE_D);
    board[RANK_8][FILE_E] = new King(BLACK, "King", RANK_8, FILE_E);
    board[RANK_8][FILE_F] = new Bishop(BLACK, "Bishop", RANK_8, FILE_F);
    board[RANK_8][FILE_G] = new Knight(BLACK, "Knight", RANK_8, FILE_G);
    board[RANK_8][FILE_H] = new Rook(BLACK, "Rook", RANK_8, FILE_H);

    // Fill the board with White Pieces
    for (int file = FILE_A; file <= FILE_H; file++)
        board[RANK_2][file] = new Pawn(WHITE, "Pawn", RANK_2, file);

    board[RANK_1][FILE_A] = new Rook(WHITE, "Rook", RANK_1, FILE_A);
    board[RANK_1][FILE_B] = new Knight(WHITE, "Knight", RANK_1, FILE_B);
    board[RANK_1][FILE_C] = new Bishop(WHITE, "Bishop", RANK_1, FILE_C);
    board[RANK_1][FILE_D] = new Queen(WHITE, "Queen", RANK_1, FILE_D);
    board[RANK_1][FILE_E] = new King(WHITE, "King", RANK_1, FILE_E);
    board[RANK_1][FILE_F] = new Bishop(WHITE, "Bishop", RANK_1, FILE_F);
    board[RANK_1][FILE_G] = new Knight(WHITE, "Knight", RANK_1, FILE_G);
    board[RANK_1][FILE_H] = new Rook(WHITE, "Rook", RANK_1, FILE_H);

    // Fill the remainder of the board with empty pieces
    for (int rank = RANK_3; rank <= RANK_6; rank++)
    {
        for (int file = FILE_A; file <= FILE_H; file++)
            board[rank][file] = new ChessPiece(NO_COLOUR, "Free", rank, file);
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
    if (isWhiteTurn)
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
    for (int rank = RANK_8; rank >= RANK_1; rank--)
    {
        std::cout << std::setw(3);
        std::cout << "|  " << rank + 1 << " ";
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            if (getChessPiece(rank, file)->getName() != "Free")
            {
                std::cout << std::setw(2) << " | ";
                if (getChessPiece(rank, file)->getColour() == BLACK)
                {
                    std::cout << "B_" << getChessPiece(rank, file)->getName()[0] << getChessPiece(rank, file)->getName()[1];
                }
                else
                {
                    std::cout << "W_" << getChessPiece(rank, file)->getName()[0] << getChessPiece(rank, file)->getName()[1];
                }
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

ChessPiece *ChessBoard::getChessPiece(int rank, int file) { return board[rank][file]; }

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
    if (!((fromRank >= RANK_1 && fromRank <= RANK_8) && (fromFile <= 'A' && fromFile <= 'G')) && ((toRank >= RANK_1 && toRank <= RANK_8) && (toFile <= 'A' && toFile <= 'G')))
    {
        std::cerr << "Not a valid board position!" << std::endl;
        return false;
    }

    // Get the piece at that position
    ChessPiece *pieceToMove = getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = getChessPiece(toRank, toFile);

    // Check if there is a piece at the position
    if (pieceToMove->isPositionFree())
    {
        std::cout << "There is no piece at position " << moveFrom << "!" << std::endl;
        return false;
    }

    // Check if the piece belongs to the player who's turn it is.
    if (isWhiteTurn && pieceToMove->getColour() == BLACK)
    {
        std::cout << "It is not Black's turn to move!" << std::endl;
        return false;
    }
    if (!isWhiteTurn && pieceToMove->getColour() == WHITE)
    {
        std::cout << "It is not White's turn to move!" << std::endl;
        return false;
    }

    // Then check if the move is valid
    if (!getChessPiece(fromRank, fromFile)->isValidMove(fromRank, fromFile, toRank, toFile, this))
    {
        // If not valid
        if (isWhiteTurn)
            std::cout << "White's " << getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;
        else
            std::cout << "Blacks's " << getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;

        return false;
    }

    // Print the move to console
    if (isWhiteTurn)
    {
        std::cout << "White's " << getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking Black's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        isWhiteTurn = false;
    }
    else
    {
        std::cout << "Black's " << getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;

        if (!targetPosition->isPositionFree())
            std::cout << " taking White's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        isWhiteTurn = true;
    }

    // Make the move, set target to piece and original position to free
    delete targetPosition;
    pieceToMove->currentFile = toFile;
    pieceToMove->currentRank = toRank;
    board[toRank][toFile] = pieceToMove;
    board[fromRank][fromFile] = new ChessPiece(NO_COLOUR, "Free", fromRank, fromFile);

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
    else if (!isCheck() && isStalemate())
    {

        std::cout << "A stalemate has occurred" << std::endl;
    }

    return true;
}