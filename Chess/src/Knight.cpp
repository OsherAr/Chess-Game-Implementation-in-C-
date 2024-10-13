#include "Knight.h"
#include <cstdlib>

bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const (*board)[8]) const {
    int rowDiff = std::abs(destRow - srcRow);
    int colDiff = std::abs(destCol - srcCol);

    // The knight moves in an L shape: 2 squares in one direction and 1 square in the perpendicular direction
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        return true;
    }

    return false;
}
