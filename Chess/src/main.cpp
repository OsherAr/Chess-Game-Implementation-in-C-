#include "Chess.h"
#include "Game.h"
#include "ResponseCodes.h"
#include <iostream>
#include <sstream>

int main() {
    // Initialize the board with a given string
    // b5d5 g5e5 a4e8 g8f8 a6d3 g1f1 e8g6
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    //string board = "R###K##R#####################################P##p#p#p#P##ppkpp##";

    Chess a(board);
    int codeResponse = 0;
    string res = a.getInput();
    Game game(board);

    while (res != "exit") {
        codeResponse = game.processInput(res);
        a.setCodeResponse(codeResponse);

        if (codeResponse == CHECKMATE) { // Checkmate
            a.displayBoard();
            std::cout << "Checkmate! " << (game.isWhiteTurn() ? "White" : "Black") << " wins.\n";
            break;
        }

        // Find the best moves
        PriorityQueue<Move, MoveComparator> pq(5);  // Max size 5
        game.getBoard().findBestMoves(game.isWhiteTurn(), pq);
        std::stringstream ss;
        ss << "Top 3 move recommendations:\n";
        for (int i = 0; i < 3 && !pq.isEmpty(); ++i) {
            ss << pq.poll().toString() << std::endl;
        }
        a.bestMove(ss.str());

        res = a.getInput();
    }

    std::cout << "Press any key to exit...\n";
    std::cin.ignore();
    std::cin.get();

    std::cout << "Exiting " << std::endl;
    return 0;
}