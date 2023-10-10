#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "board.hpp"

/*
To-do
1) Add ability to restart game upon completion
2) Make game board look nicer 
3) Add more input validation (Can't enter non-numbers etc) and improve piece movement input
4) Add King functionality
5) Add ability to take multiple pieces where possible
6) Write scores to file
*/

bool coordinate_validation(std::string orig_coordinates, std::string new_coordinates) {
    if (orig_coordinates.length() != 3 || new_coordinates.length() != 3)
        return false;
    if (!isdigit(orig_coordinates[0]) || !isdigit(orig_coordinates[2]) || !isdigit(new_coordinates[0]) || !isdigit(new_coordinates[2]))
        return false;
    if (int(orig_coordinates[0] - 48) < 1 || int(orig_coordinates[0] - 48) > 8 || int(orig_coordinates[2] - 48) < 1 || int(orig_coordinates[2] - 48) > 8 
    || int(new_coordinates[0] - 48) < 1 || int(new_coordinates[0] - 48) > 8 || int(new_coordinates[2] - 48) < 1 || int(new_coordinates[2] - 48) > 8)
        return false;
    return true;
}

void displayGameBoard(CheckersBoard board) {
    std::cout << "\n-------------------------------------\n";
    for (int x=0; x <= board.getBoard().size(); x++) {
        if (x < board.getBoard().size())
            std::cout << "| " << x+1 << " ";
        else
            std::cout << "| " << "  ";
        for (int y=0; y < board.getBoard()[0].size(); y++) {
            if (x < board.getBoard()[0].size())
                if (board.getBoard()[x][y].getKing())
                    std::cout << "| " << char(toupper(board.getBoard()[x][y].getColour())) << " ";
                else
                    std::cout << "| " << board.getBoard()[x][y].getColour() << " ";
            else
                std::cout << "| " << y+1 << " ";
        }
        std::cout << "|\n-------------------------------------\n";
    }
}

int main() {
    bool play_game = true;
    bool turn_valid;
    std::string orig_coordinates, new_coordinates;
    int x_orig, y_orig, x_new, y_new;
    std::string play_again;
    do {
        CheckersBoard board;
        char turn = 'r';
        do {
            do {
                displayGameBoard(board);
                turn == 'r' ? std::cout << "RED TURN\n" : std::cout << "BLACK TURN\n";
                std::cout << "Enter the coordinates of the piece you want to move in the form a,b: ";
                std::cin >> orig_coordinates;
                std::cout << "Enter the coordinates of where you want to move the piece to in the form a,b: ";
                std::cin >> new_coordinates;
                turn_valid = coordinate_validation(orig_coordinates, new_coordinates);
                if (!turn_valid) {
                    std::cout << "Some of the coordinates entered are invalid, please try again.\n\n";
                }
                else {
                    turn_valid = board.checkPiece(int(orig_coordinates[0] - 48)-1, int(orig_coordinates[2] - 48)-1, turn);
                    if (turn_valid) {
                        checkersPiece piece = board.findPiece(int(orig_coordinates[0] - 48)-1, int(orig_coordinates[2] - 48)-1);
                        turn_valid = board.movePiece(piece, int(new_coordinates[0] - 48)-1, int(new_coordinates[2] - 48)-1);
                        if (!turn_valid)
                            std::cout << "Move made is invalid, please try again.\n\n";
                    }
                    else
                        std::cout << "Piece selected is not valid, please try again.\n\n";
                }
            } while(turn_valid == false);
            board.checkForKing();
            turn == 'r' ? turn = 'b' : turn = 'r'; 
        } while (board.getRed() > 0 && board.getBlack() > 0);

        if (board.getRed() <= 0) {
            std::cout << "Black has won!\n";
        }
        else {
            std::cout << "Red has won!\n";
        }
        displayGameBoard(board);
        std::cout << "Do you want to play again: ";
        std::cin >> play_again;
        play_again == "yes" || play_again == "y" ? play_game = true : play_game = false;
    } while (play_game);
    std::cout << "Game Over";
}