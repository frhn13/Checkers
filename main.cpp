#include <iostream>
#include <vector>
#include "board.hpp"

int main() {
    CheckersBoard board;
    std::vector<std::vector<checkersPiece>> game_board = board.createBoard();
    for (int x=0; x < game_board.size(); x++) {
        for (int y=0; y < game_board[0].size(); y++) {
            std::cout  << "| " << game_board[x][y].getColour() << " ";
        }
        std::cout << "|\n---------------------------------\n";
    }
}