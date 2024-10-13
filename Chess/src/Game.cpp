#include "Game.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "ResponseCodes.h"
#include <iostream>

int Game::processInput(const string& input) {
    int srcRow = input[0] - 'a';
    int srcCol = input[1] - '1';
    int destRow = input[2] - 'a';
    int destCol = input[3] - '1';

    Piece* srcPiece = board.getPiece(srcRow, srcCol);
    Piece* destPiece = board.getPiece(destRow, destCol);

    if (!srcPiece) {
        std::cout << "No piece at source position\n";
        return NO_PIECE_AT_SOURCE;
    }

    if (srcPiece->isWhitePiece() != turn) {
        std::cout << "Piece belongs to the opponent\n";
        return OPPONENT_PIECE_AT_SOURCE;
    }

    if (destPiece && destPiece->isWhitePiece() == turn && !(srcPiece->getSymbol() == 'K' && destPiece->getSymbol() == 'R')) {
        std::cout << "Destination occupied by same color piece\n";
        return SAME_COLOR_PIECE_AT_DEST;
    }

    if (!srcPiece->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard())) {
        std::cout << "Invalid move for the piece\n";
        return ILLEGAL_MOVE;
    }

    if ((srcPiece->getSymbol() == 'K' || srcPiece->getSymbol() == 'k') && srcCol == 4 && (destCol == 0 || destCol == 7)) {
        int rookSrcCol = destCol;
        int rookDestCol = (destCol == 0) ? 3 : 5;
        int kingDestCol = (destCol == 0) ? 2 : 6;
        board.movePiece(srcRow, srcCol, srcRow, kingDestCol); // Move the king
        board.movePiece(srcRow, rookSrcCol, srcRow, rookDestCol); // Move the rook

        dynamic_cast<King*>(srcPiece)->setMoved(true);
        dynamic_cast<Rook*>(board.getPiece(srcRow,rookDestCol))->setMoved(true);
        switchTurn();
        return CASTLING_MOVE;
    }

    Piece* tempDest = destPiece;
    board.movePiece(srcRow, srcCol, destRow, destCol);

    if (board.isCheck(turn)) {
        board.movePiece(destRow, destCol, srcRow, srcCol);
        board.setPiece(destRow, destCol, tempDest);
        std::cout << "Move would cause check\n";
        return MOVE_CAUSES_CHECK;
    }

    if (Pawn* pawn = dynamic_cast<Pawn*>(srcPiece)) {
        if (pawn->isPromotion(destRow)) {
            std::cout << "Pawn promotion! Enter new piece type (Q/R/B/N): ";
            char newPieceType;
            std::cin >> newPieceType;
            if (!board.promotePawn(destRow, destCol, newPieceType)) {
                return INVALID_PROMOTION;
            }
            switchTurn();
            return PROMOTION;
        }
    }

    if (board.isCheck(!turn)) {
        if (board.isCheckmate(!turn)) {
            std::cout << "Checkmate detected for " << (turn ? "Black" : "White") << std::endl;
            return CHECKMATE;
        }
        return MOVE_CAUSES_CHECKMATE;
    }
    switchTurn();
    return LEGAL_MOVE;
}
