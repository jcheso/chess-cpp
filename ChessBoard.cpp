#include "ChessBoard.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "Bishop.h"
#include "ChessPiece.h"
#include "Helper.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

ChessBoard::ChessBoard() { setBoard(); }
ChessBoard::~ChessBoard() { clearBoard(); }

// ** PRIVATE GETTERS **

bool ChessBoard::isWhiteTurn() {
    if (currentPlayer == WHITE)
        return true;
    else
        return false;
}

void ChessBoard::getKingCoordinates(int &kingRank, int &kingFile) {
    // Iterate through every position on the board until the King of the desired colour is found
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            if (getChessPiece(rank, file)->getName() == "King" && getChessPiece(rank, file)->getColour() == currentPlayer) {
                kingRank = rank;
                kingFile = file;
            }
        }
    }
}

bool ChessBoard::pieceCanBeTaken(int rankToCheck, int fileToCheck) {
    // Iterate through every position on the board, if it is the oppositeTeams piece see if it can take the piece
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            ChessPiece *thisPiece = getChessPiece(rank, file);
            if ((thisPiece->getColour() == oppositionPlayer) && (thisPiece->isMoveValid(rank, file, rankToCheck, fileToCheck, this)))
                return true;
        }
    }
    return false;
}

bool ChessBoard::parseInput(std::string moveFrom, std::string moveTo, int &fromRank, int &fromFile, int &toRank, int &toFile) {
    // Parse the input strings into two sets of coordinates
    fromRank = moveFrom[1] - 1 - '0';
    fromFile = moveFrom[0] - 'A';
    toRank = moveTo[1] - 1 - '0';
    toFile = moveTo[0] - 'A';

    // Check if it is a valid board position
    if (!((fromRank >= RANK_1 && fromRank <= RANK_8) && (fromFile <= 'A' && fromFile <= 'G')) && ((toRank >= RANK_1 && toRank <= RANK_8) && (toFile <= 'A' && toFile <= 'G'))) {
        std::cerr << "Not a valid board position!" << std::endl;
        return false;
    } else
        return true;
}

bool ChessBoard::isCheck() {
    int kingToCheckRank, kingToCheckFile;
    // Get the coordinates of the King to find out if it is in check
    getKingCoordinates(kingToCheckRank, kingToCheckFile);
    // Check if the King can be taken, if so return true for king in check
    if (pieceCanBeTaken(kingToCheckRank, kingToCheckFile))
        return true;
    else
        return false;
}

// !! WHY IS THIS TRIGGERING ON LINUX BUT NOT WINDOWS
bool ChessBoard::isCheckmate() {
    int kingRank, kingFile, attackingPieceCount, attackingPieceRank, attackingPieceFile;

    getKingCoordinates(kingRank, kingFile);
    ChessPiece *king = getChessPiece(kingRank, kingFile);

    // Test if the King can move somewhere it's not in check
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            // Check if it can move somewhere, then check if it is still in check in that move - repeat for all possible moves
            if (king->isMoveValid(kingRank, kingFile, rank, file, this)) {
                // If the move is valid, place a temp king in that position
                ChessPiece *originalPiece = board[rank][file];
                board[rank][file] = new King(currentPlayer, "King", rank, file);

                // Check if that king is in check
                if (!pieceCanBeTaken(rank, file)) {
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

    // Check if a piece can make a move that interposes the check
    if (!moveResultsInCheck())
        return false;

    // Check how many pieces can take the King
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            ChessPiece *thisPiece = getChessPiece(rank, file);
            if (thisPiece->getColour() == oppositionPlayer && thisPiece->isMoveValid(rank, file, kingRank, kingFile, this)) {
                attackingPieceFile = file;
                attackingPieceRank = rank;
                attackingPieceCount++;
            }
        }
    }

    // If no pieces can take the king, return false to checkmate
    if (attackingPieceCount < 1)
        return false;
    // If only one piece can take it, check if the player in Check can take that piece with a valid move. Return false if it can => not in Checkmate
    else if (attackingPieceCount == 1) {
        for (int rank = RANK_8; rank >= RANK_1; rank--) {
            for (int file = FILE_A; file <= FILE_H; file++) {
                ChessPiece *thisPiece = getChessPiece(rank, file);
                if (thisPiece->getColour() == currentPlayer && thisPiece->isMoveValid(rank, file, attackingPieceRank, attackingPieceFile, this))
                    return false;
            }
        }
    }
    // If king cannot move, check can not be interposed and attacking piece cannot be taken return true to checkmate
    return true;
}

bool ChessBoard::moveResultsInCheck() {
    int rankTo, fileTo;

    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            // Check if any piece has a valid move that doesn't result in the King being checked
            if (getChessPiece(rank, file)->getColour() == currentPlayer && getChessPiece(rank, file)->hasValidMove(rankTo, fileTo, this)) {
                // Swap the pieces temporarily so isCheck() considers the move
                ChessPiece *originalPiece = board[rankTo][fileTo];
                ChessPiece *pieceToMove = board[rank][file];
                board[rankTo][fileTo] = pieceToMove;
                board[rank][file] = new ChessPiece(NO_COLOUR, "Free", rank, file);

                // If moving the piece results in a check
                if (isCheck()) {
                    // Delete the temp piece from memory and restore original state, return stalemate as in check after move
                    delete getChessPiece(rank, file);
                    board[rankTo][fileTo] = originalPiece;
                    board[rank][file] = pieceToMove;
                    return true;
                } else {
                    // Delete the temp piece from memory and restore original state, return no stalemate as not in check after move
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

void ChessBoard::checkGameConditions() {
    if (isWhiteTurn() && isCheck()) {
        if (isCheckmate())
            std::cout << "White is in checkmate" << std::endl;
        else
            std::cout << "White is in check" << std::endl;
    } else if (!isWhiteTurn() && isCheck()) {
        if (isCheckmate())
            std::cout << "Black is in checkmate" << std::endl;
        else
            std::cout << "Black is in check" << std::endl;
    } else if (!isCheck() && moveResultsInCheck())
        std::cout << "A stalemate has occurred" << std::endl;
}

bool ChessBoard::isPlayersTurn(ChessPiece *pieceToMove) {
    // Check if the piece belongs to the player who's turn it is.
    if (isWhiteTurn() && pieceToMove->getColour() == BLACK) {
        std::cout << "It is not Black's turn to move!" << std::endl;
        return false;
    }
    if (!isWhiteTurn() && pieceToMove->getColour() == WHITE) {
        std::cout << "It is not White's turn to move!" << std::endl;
        return false;
    } else
        return true;
}

// ** PRIVATE SETTERS **

void ChessBoard::setBoard() {
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
    for (int rank = RANK_3; rank <= RANK_6; rank++) {
        for (int file = FILE_A; file <= FILE_H; file++)
            board[rank][file] = new ChessPiece(NO_COLOUR, "Free", rank, file);
    }

    std::cout << "A new chess game is started!" << std::endl;

    // Set the starting turns
    currentPlayer = WHITE;
    oppositionPlayer = BLACK;
}

void ChessBoard::clearBoard() {
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++)
            delete board[rank][file];
    }
}

// ** PRIVATE HELPERS **

void ChessBoard::printMove(ChessPiece *targetPosition, int fromRank, int fromFile, std::string moveFrom, std::string moveTo) {
    if (isWhiteTurn()) {
        std::cout << "White's " << getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking Black's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        currentPlayer = BLACK;
        oppositionPlayer = WHITE;
    } else {
        std::cout << "Black's " << getChessPiece(fromRank, fromFile)->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking White's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
        currentPlayer = WHITE;
        oppositionPlayer = BLACK;
    }
}

// ** PUBLIC GETTERS **

ChessPiece *ChessBoard::getChessPiece(int rank, int file) { return board[rank][file]; }

void ChessBoard::printBoard() {
    std::cout
        << "\n"
        << "|----------------------------------------------------------------------------------|" << std::endl;
    if (isWhiteTurn())
        std::cout << std::setw(20) << "|                            **White's turn to move!**                             |" << std::endl;
    else
        std::cout << std::setw(20) << "|                            **Black's turn to move!**                             |" << std::endl;
    std::cout
        << "|----------------------------------------------------------------------------------|" << std::endl;
    std::cout << std::setw(2) << "|     ";
    std::cout << "|   A  |  |  B   |  |  C   |  |  D   |  |  E   |  |  F   |  |  G   |  |  H   |" << std::endl;
    std::cout
        << "|----------------------------------------------------------------------------------|" << std::endl;
    // std::cout << std::setw(2) << " | "
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        std::cout << std::setw(3);
        std::cout << "|  " << rank + 1 << " ";
        for (int file = FILE_A; file <= FILE_H; file++) {
            if (getChessPiece(rank, file)->getName() != "Free") {
                std::cout << std::setw(2) << " | ";
                if (getChessPiece(rank, file)->getColour() == BLACK)
                    std::cout << "B_" << getChessPiece(rank, file)->getName()[0] << getChessPiece(rank, file)->getName()[1];
                else
                    std::cout << "W_" << getChessPiece(rank, file)->getName()[0] << getChessPiece(rank, file)->getName()[1];
                std::cout << std::setw(2) << " | ";
            } else {
                std::cout << std::setw(2) << " | ";
                std::cout << std::setw(7) << " | ";
            }
        }
        std::cout << "\n"
                  << "|----------------------------------------------------------------------------------|" << std::endl;
    }
}

// ** PUBLIC SETTERS **
// TODO: Don't let player move if they are in checkmate
// TODO: Don't let player move anything other than a move that gets them out of check
// TODO: Don't let players move if it is a stalemate

bool ChessBoard::submitMove(std::string moveFrom, std::string moveTo) {
    int fromRank, fromFile, toRank, toFile;
    parseInput(moveFrom, moveTo, fromRank, fromFile, toRank, toFile);

    // Get the pieces at each position
    ChessPiece *pieceToMove = getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = getChessPiece(toRank, toFile);

    // Check if there is a piece at the position
    if (pieceToMove->isPositionFree()) {
        std::cout << "There is no piece at position " << moveFrom << "!" << std::endl;
        return false;
    }

    // If it is not the players turn or the move isn't valid, print to console that move is not valid
    if (!isPlayersTurn(pieceToMove) || !pieceToMove->isMoveValid(fromRank, fromFile, toRank, toFile, this)) {
        if (isWhiteTurn())
            std::cout << "White's " << getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;
        else
            std::cout << "Blacks's " << getChessPiece(fromRank, fromFile)->getName() << " cannot move to " << moveTo << std::endl;
        return false;
    }

    // Print the move to console
    printMove(targetPosition, fromRank, fromFile, moveFrom, moveTo);

    // Move the piece, update its position and set the old location to Free
    delete targetPosition;
    board[toRank][toFile] = pieceToMove;
    pieceToMove->updatePosition(toRank, toFile);
    board[fromRank][fromFile] = new ChessPiece(NO_COLOUR, "Free", fromRank, fromFile);

    // Check for end of turn game conditions (check, checkmate, stalemate)
    checkGameConditions();

    return true;
}

void ChessBoard::resetBoard() {
    clearBoard();
    setBoard();
}
