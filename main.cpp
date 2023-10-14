#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include "board.hpp"

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

void writeScoreToFile(std::string winner, int winner_pieces) {
    std::ofstream scores;
    scores.open("scores.txt", std::ios::app);
    std::string score = winner + " won with " + std::to_string(winner_pieces) + " pieces left\n";
    scores << score;
    scores.close();
}

std::vector<std::string> readScoresFromFile() {
    std::string score;
    std::vector<std::string> scores;
    std::ifstream scores_file("scores.txt");
    if (scores_file.is_open()) {
        while (std::getline(scores_file, score)) {
            scores.push_back(score);
        }
    }
    return scores;
}

int main() {
    bool play_game = true;
    bool turn_valid;
    std::string orig_coordinates, new_coordinates;
    int x_orig, y_orig, x_new, y_new;
    std::string move_again;
    std::string play_again;
    std::string new_orig_coordinates;
    std::string previous_results;
    do {
        CheckersBoard board;
        char turn = 'r';
        int no_red = board.getRed(), no_black = board.getBlack();

        std::cout << "Would you like to see the results from previous games of checkers, answer with yes or no: ";
            std::cin >> previous_results;
            if (strcasecmp(previous_results.c_str(), "yes") == 0) {
                std::vector<std::string> scores_list = readScoresFromFile();
                if (scores_list.size() == 0)
                    std::cout << "No scores are present";
                for (int x=0; x<scores_list.size(); x++) {
                    std::cout << scores_list[x] << std::endl;
                }
                std::cout << std::endl;
            }

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
                        turn_valid = board.movePiece(piece, int(new_coordinates[0] - 48)-1, int(new_coordinates[2] - 48)-1, false);
                        if (!turn_valid)
                            std::cout << "Move made is invalid, please try again.\n\n";
                    }
                    else
                        std::cout << "Piece selected is not valid, please try again.\n\n";
                }
            } while(turn_valid == false);
            new_orig_coordinates = new_coordinates;
            if (no_red > board.getRed() || no_black > board.getBlack()) {
                do {
                    displayGameBoard(board);
                    std::cout << "Can you move that piece again, answer with Yes or No: ";
                    std::cin >> move_again;
                    if (strcasecmp(move_again.c_str(), "yes") == 0) {
                        orig_coordinates = new_orig_coordinates;
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
                                turn_valid = board.movePiece(piece, int(new_coordinates[0] - 48)-1, int(new_coordinates[2] - 48)-1, true);
                                if (!turn_valid)
                                    std::cout << "Move made is invalid, please try again.\n\n";
                                else
                                    new_orig_coordinates = new_coordinates;
                            }
                            else
                                std::cout << "Piece selected is not valid, please try again.\n\n";
                        }
                    }
                } while(strcasecmp(move_again.c_str(), "yes") == 0);
            }
            board.checkForKing();
            no_red = board.getRed();
            no_black = board.getBlack();
            turn == 'r' ? turn = 'b' : turn = 'r'; 
        } while (board.getRed() > 0 && board.getBlack() > 0);

        if (board.getRed() <= 0) {
            std::cout << "Black has won!\n";
            writeScoreToFile("Black", board.getBlack());
        }
        else {
            std::cout << "Red has won!\n";
            writeScoreToFile("Red", board.getRed());
        }
        displayGameBoard(board);
        std::cout << "Do you want to play again: ";
        std::cin >> play_again;
        strcasecmp(move_again.c_str(), "yes") == 0 || play_again == "y" ? play_game = true : play_game = false;
    } while (play_game);
    std::cout << "Game Over";
}