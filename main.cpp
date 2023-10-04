#include <iostream>
#include <vector>
#include "board.hpp"

void displayGameBoard(CheckersBoard board) {
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

int main() {
    CheckersBoard board;
    int x_orig, y_orig, x_new, y_new;
    char turn = 'r';
    bool turn_valid;
    do {
        displayGameBoard(board);
        do {
            turn == 'r' ? std::cout << "RED TURN\n" : std::cout << "BLACK TURN\n";
            std::cout << "Enter the x coordinate of the piece you want to move: ";
            std::cin >> x_orig;
            std::cout << "Enter the y coordinate of the piece you want to move: ";
            std::cin >> y_orig;
            std::cout << "Enter the x coordinate of where you want to move the piece to: ";
            std::cin >> x_new;
            std::cout << "Enter the y coordinate of where you want to move the piece to: ";
            std::cin >> y_new;
            turn_valid = board.checkPiece(x_orig-1, y_orig-1, turn);
            if (turn_valid) {
                checkersPiece piece = board.findPiece(x_orig-1, y_orig-1);
                turn_valid = board.movePiece(piece, x_new-1, y_new-1);
                if (!turn_valid)
                    std::cout << "Move made is invalid, please try again.\n\n";
            }
            else
                std::cout << "Piece selected is not valid, please try again.\n\n";
        } while(turn_valid == false);
        turn == 'r' ? turn = 'b' : turn = 'r'; 
    } while (board.getRed() > 0 || board.getBlack() > 0);
}