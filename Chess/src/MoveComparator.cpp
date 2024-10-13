#include "MoveComparator.h"

int MoveComparator::operator()(const Move& a, const Move& b) const {
    // Higher score moves should come first
    return b.getScore() - a.getScore();
}
