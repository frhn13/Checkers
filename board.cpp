#include <vector>
#include "board.hpp"
#include <iostream>

std::vector<std::vector<checkersPiece>> CheckersBoard::createBoard() {
    const int BOARD_SIZE = 8;
    std::vector<std::vector<checkersPiece>> game_board(8);
    for (int x=0; x<BOARD_SIZE; x++) {
        for (int y=0; y<BOARD_SIZE; y++) {
            checkersPiece piece('r', true, x, y, false);
            if (x < 3 && (x+y)%2 == 1) {
                piece.setColour('r');
                piece.setAlive(true);
            }
            else if (x > 4 && (x+y)%2 == 1) {
                piece.setColour('b');
                piece.setAlive(true);
            }
            else {
                piece.setColour('n');
                piece.setAlive(false);   
            }
            game_board[x].push_back(piece);
        }
    }
    return game_board;
}