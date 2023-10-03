#include <iostream>
#include <vector>
#include "board.hpp"

int main() {
    CheckersBoard board;
    // std::vector<std::vector<checkersPiece>> game_board = board.getBoard();
    for (int x=0; x <= board.getBoard().size(); x++) {
        if (x < board.getBoard().size())
            std::cout << "| " << x+1 << " ";
        else
            std::cout << "| " << "  ";
        for (int y=0; y < board.getBoard()[0].size(); y++) {
            if (x < board.getBoard()[0].size())
                std::cout << "| " << board.getBoard()[x][y].getColour() << " ";
            else
                std::cout << "| " << y+1 << " ";
        }
        std::cout << "|\n-------------------------------------\n";
    }
    std::cout << "\n\n";
    checkersPiece piece = board.findPiece(5, 0);
    board.movePiece(piece, 4, 1);

    for (int x=0; x <= board.getBoard().size(); x++) {
        if (x < board.getBoard().size())
            std::cout << "| " << x+1 << " ";
        else
            std::cout << "| " << "  ";
        for (int y=0; y < board.getBoard()[0].size(); y++) {
            if (x < board.getBoard()[0].size())
                std::cout << "| " << board.getBoard()[x][y].getColour() << " ";
            else
                std::cout << "| " << y+1 << " ";
        }
        std::cout << "|\n-------------------------------------\n";
    }
}