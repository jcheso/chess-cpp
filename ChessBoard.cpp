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
            if ((thisPiece->getColour() == oppositionPlayer) && (thisPiece->isMoveValid(rankToCheck, fileToCheck, this)))
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
    getKingCoordinates(kingToCheckRank, kingToCheckFile);
    if (pieceCanBeTaken(kingToCheckRank, kingToCheckFile))
        return true;
    else
        return false;
}

bool ChessBoard::isCheckmate() {
    int kingRank, kingFile;
    getKingCoordinates(kingRank, kingFile);
    if (canInterposeCheck() || canKingMoveOutOfCheck(kingRank, kingFile) || canCaptureAttackingPiece(kingRank, kingFile))
        return false;
    return true;
}

bool ChessBoard::canInterposeCheck() {
    // Check if there is a valid move where this piece can no longer take the king
    for (int rankFrom = RANK_8; rankFrom >= RANK_1; rankFrom--) {
        for (int fileFrom = FILE_A; fileFrom <= FILE_H; fileFrom++) {
            // Find each piece on the checked players team and see if they can block the attack
            if (getChessPiece(rankFrom, fileFrom)->getColour() == currentPlayer && pieceCanBlockAttack(rankFrom, fileFrom))
                return true;
        }
    }
    return false;
}

bool ChessBoard::pieceCanBlockAttack(int rankFrom, int fileFrom) {
    ChessPiece *thisPiece = getChessPiece(rankFrom, fileFrom);
    for (int rankTo = RANK_8; rankTo >= RANK_1; rankTo--) {
        for (int fileTo = FILE_A; fileTo <= FILE_H; fileTo++) {
            // If the move is valid, check if the player is still in check
            if (thisPiece->isMoveValid(rankTo, fileTo, this)) {
                // Temporarily make the move
                ChessPiece *originalPiece = board[rankTo][fileTo];
                board[rankFrom][fileFrom] = new ChessPiece(NO_COLOUR, "Free", rankFrom, fileFrom);
                board[rankTo][fileTo] = thisPiece;
                // Check if the player is still in check with this move in place
                if (!isCheck()) {
                    // Remove the new piece from memory & restore the original board condition
                    delete board[rankFrom][fileFrom];
                    board[rankFrom][fileFrom] = thisPiece;
                    board[rankTo][fileTo] = originalPiece;
                    // If player is not in check, return true to being interposed
                    return true;
                } else {
                    // Remove the new piece from memory & restore the original board condition
                    delete board[rankFrom][fileFrom];
                    board[rankFrom][fileFrom] = thisPiece;
                    board[rankTo][fileTo] = originalPiece;
                }
            }
        }
    }
    return false;
}

bool ChessBoard::canKingMoveOutOfCheck(int kingRank, int kingFile) {
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            // Check if it can move somewhere, then check if it is still in check in that move - repeat for all possible moves
            if (getChessPiece(kingRank, kingFile)->isMoveValid(rank, file, this)) {
                // If the move is valid, place a temp king in that position
                ChessPiece *originalPiece = board[rank][file];
                board[rank][file] = new King(currentPlayer, "King", rank, file);
                // Check if that king is in check
                if (!pieceCanBeTaken(rank, file)) {
                    // If the king is no longer in check, restore the original free space and return true
                    delete getChessPiece(rank, file);
                    board[rank][file] = originalPiece;
                    return true;
                }
                // If the king is still in check regardless of the space, restore the free space and move on with the other checks.
                delete getChessPiece(rank, file);
                board[rank][file] = originalPiece;
            }
        }
    }
    return false;
}

bool ChessBoard::canCaptureAttackingPiece(int kingRank, int kingFile) {
    int attackingPieceCount, attackingPieceRank, attackingPieceFile;
    // Count how many pieces can take the king
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            ChessPiece *thisPiece = getChessPiece(rank, file);
            if (thisPiece->getColour() == oppositionPlayer && thisPiece->isMoveValid(kingRank, kingFile, this)) {
                attackingPieceRank = rank;
                attackingPieceFile = file;
                attackingPieceCount++;
            }
        }
    }
    // If only one piece can take it, check if the player in Check can take that piece with a valid move.
    if (attackingPieceCount == 1) {
        for (int rank = RANK_8; rank >= RANK_1; rank--) {
            for (int file = FILE_A; file <= FILE_H; file++) {
                ChessPiece *thisPiece = getChessPiece(rank, file);
                if (thisPiece->getColour() == currentPlayer && thisPiece->isMoveValid(attackingPieceRank, attackingPieceFile, this))
                    return true;
            }
        }
    }
    return false;
}

bool ChessBoard::isStalemate() {
    int rankTo, fileTo;
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            // Check if any piece has a valid move
            ChessPiece *thisPiece = getChessPiece(rank, file);
            if (thisPiece->getColour() == currentPlayer && thisPiece->hasValidMove(rankTo, fileTo, this)) {
                // Swap the pieces temporarily so isCheck() considers the move
                ChessPiece *originalPiece = board[rankTo][fileTo];
                ChessPiece *pieceToMove = board[rank][file];
                board[rankTo][fileTo] = pieceToMove;
                board[rank][file] = new ChessPiece(NO_COLOUR, "Free", rank, file);
                // If moving the piece results in a check return true to stalemate, restore original condition either way
                if (isCheck()) {
                    delete getChessPiece(rank, file);
                    board[rankTo][fileTo] = originalPiece;
                    board[rank][file] = pieceToMove;
                    return true;
                } else {
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

void ChessBoard::checkGameStatus() {
    if (isWhiteTurn() && isCheck()) {
        if (isCheckmate()) {
            std::cout << "White is in checkmate" << std::endl;
            checkmate = true;
        } else {
            std::cout << "White is in check" << std::endl;
            whiteInCheck = true;
        }
    } else if (!isWhiteTurn() && isCheck()) {
        if (isCheckmate()) {
            std::cout << "Black is in checkmate" << std::endl;
            checkmate = true;
        } else {
            std::cout << "Black is in check" << std::endl;
            blackInCheck = true;
        }
    } else if (!isCheck() && isStalemate()) {
        std::cout << "A stalemate has occurred" << std::endl;
        stalemate = true;
    } else {
        whiteInCheck = false;
        blackInCheck = false;
    }
}

bool ChessBoard::isPlayersTurn(ChessPiece *pieceToMove) {
    if (isWhiteTurn() && pieceToMove->getColour() == BLACK) {
        std::cout << "It is not Black's turn to move!" << std::endl;
        return false;
    }
    if (!isWhiteTurn() && pieceToMove->getColour() == WHITE) {
        std::cout << "It is not White's turn to move!" << std::endl;
        return false;
    }
    return true;
}

bool ChessBoard::moveNotValid(ChessPiece *pieceToMove, std::string moveFrom, std::string moveTo, int toRank, int toFile) {
    if (checkmate == true || stalemate == true) {
        std::cout << "Please reset the board to start a new game, this game has ended" << std::endl;
        return true;
    }
    // Check if there is a piece at the position to move
    if (pieceToMove->isPositionFree()) {
        std::cout << "There is no piece at position " << moveFrom << "!" << std::endl;
        return true;
    }
    // If it is not the players turn or the move isn't valid, print to console that move is not valid
    if (!isPlayersTurn(pieceToMove) || !pieceToMove->isMoveValid(toRank, toFile, this)) {
        if (isWhiteTurn())
            std::cout << "White's " << pieceToMove->getName() << " cannot move to " << moveTo << std::endl;
        else
            std::cout << "Blacks's " << pieceToMove->getName() << " cannot move to " << moveTo << std::endl;
        return true;
    }
    return false;
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
    currentPlayer = WHITE, oppositionPlayer = BLACK;
    whiteInCheck = false, blackInCheck = false, checkmate = false, stalemate = false;
}

void ChessBoard::clearBoard() {
    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++)
            delete board[rank][file];
    }
}

void ChessBoard::swapTurn() {
    if (isWhiteTurn()) {
        currentPlayer = BLACK;
        oppositionPlayer = WHITE;
    } else {
        currentPlayer = WHITE;
        oppositionPlayer = BLACK;
    }
}

bool ChessBoard::causingSelfCheck(int fromRank, int fromFile, int toRank, int toFile, std::string moveTo) {
    ChessPiece *pieceToMove = getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = getChessPiece(toRank, toFile);

    // Make the move on the board
    board[toRank][toFile] = pieceToMove;
    pieceToMove->updatePosition(toRank, toFile);
    board[fromRank][fromFile] = new ChessPiece(NO_COLOUR, "Free", fromRank, fromFile);

    // If a move resulted in check or checkmate for current player, reverse it and return true to causing a self check
    if (isCheck() || isCheckmate()) {
        if (isWhiteTurn())
            std::cout << "White's " << getChessPiece(toRank, toFile)->getName() << " cannot move to " << moveTo << " because Black will still be in check" << std::endl;
        else
            std::cout << "Blacks's " << getChessPiece(toRank, toFile)->getName() << " cannot move to " << moveTo << " because White will still be in check" << std::endl;
        delete getChessPiece(fromRank, fromFile);
        board[fromRank][fromFile] = pieceToMove;
        pieceToMove->updatePosition(fromRank, fromFile);
        board[toRank][toFile] = targetPosition;
        return true;
    }
    delete targetPosition;
    return false;
}

// ** PRIVATE HELPERS **

void ChessBoard::printMove(ChessPiece *targetPosition, ChessPiece *pieceToMove, std::string moveFrom, std::string moveTo) {
    if (isWhiteTurn()) {
        std::cout << "White's " << pieceToMove->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking Black's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
    } else {
        std::cout << "Black's " << pieceToMove->getName() << " moves from "
                  << moveFrom << " to " << moveTo;
        if (!targetPosition->isPositionFree())
            std::cout << " taking White's " << targetPosition->getName() << endl;
        else
            std::cout << "\n";
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

bool ChessBoard::submitMove(std::string moveFrom, std::string moveTo) {
    int fromRank, fromFile, toRank, toFile;
    parseInput(moveFrom, moveTo, fromRank, fromFile, toRank, toFile);

    ChessPiece *pieceToMove = getChessPiece(fromRank, fromFile);
    ChessPiece *targetPosition = getChessPiece(toRank, toFile);

    if (moveNotValid(pieceToMove, moveFrom, moveTo, toRank, toFile) || causingSelfCheck(fromRank, fromFile, toRank, toFile, moveTo))
        return false;
    else {
        printMove(targetPosition, pieceToMove, moveFrom, moveTo);
        swapTurn();
        checkGameStatus();
        return true;
    }
    return false;
}

void ChessBoard::resetBoard() {
    clearBoard();
    setBoard();
}
