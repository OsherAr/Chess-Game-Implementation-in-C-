# Chess Game

## Custom Exceptions

### InvalidMoveException
Thrown when an invalid move is attempted. It inherits from `std::exception` and provides a custom error message.

### PromotionException
Thrown when an invalid pawn promotion is attempted. It inherits from `std::exception` and provides a custom error message.

## Algorithm for Best Move Recommendation

### Priority Queue Implementation
The `PriorityQueue` class is implemented using a list from the STL. It supports two main operations:

- `push(const T& value)`: Adds a value to the queue in the correct position based on the comparator. If the queue exceeds the maximum size, the lowest priority item is removed.
- `poll()`: Removes and returns the highest priority item from the queue.

### Move Scoring Algorithm
The algorithm for scoring moves is as follows:

1. **Capture Moves**: Moves that capture an opponent's piece are scored higher.
    - Capturing a queen: +50 points
    - Capturing a rook: +30 points
    - Other captures: +10 points
2. **Additional Scoring**: Additional logic can be added to score moves based on other criteria, such as controlling the center of the board or putting the opponent in check.

### Usage
The `BestMove` class uses the priority queue to find and recommend the best moves. It evaluates all possible moves for the current player and scores them using the scoring algorithm. The top 5 moves are then stored in the priority queue and recommended to the player.
