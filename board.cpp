#include <vector>
#include "board.hpp"
#include <iostream>

CheckersBoard::CheckersBoard() {
    const int NO_PIECES = 12;
    this->board = CheckersBoard::createBoard();
    this->no_red = NO_PIECES;
    this->no_black = NO_PIECES;
}

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
                piece.setColour(' ');
                piece.setAlive(false);   
            }
            game_board[x].push_back(piece);
        }
    }
    return game_board;
}

std::vector<std::vector<checkersPiece>> CheckersBoard::getBoard() {
    return this->board;
}

int CheckersBoard::getRed() {
    return this->no_red;
}

int CheckersBoard::getBlack() {
    return this->no_black;
}

void CheckersBoard::decreaseRed() {
    this->no_red--;
}

void CheckersBoard::decreaseBlack() {
    this->no_black--;
}

checkersPiece CheckersBoard::findPiece(int row, int column) {
    return this->board[row][column];
}

bool CheckersBoard::checkPiece(int row, int column, char turn) {
    return this->board[row][column].getColour() == turn ? true : false;
}

bool CheckersBoard::movePiece(checkersPiece piece, int new_row, int new_column) {
    checkersPiece moved_to_piece = CheckersBoard::findPiece(new_row, new_column);
    if (piece.getColour() == 'r') {
        if (piece.getRow()+1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' ') {
            piece.setColour(' ');
            moved_to_piece.setColour('r');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row-1][new_column-1].getColour() == 'b') {
            checkersPiece destroyed_piece = CheckersBoard::findPiece(new_row-1, new_column-1);
            piece.setColour(' ');
            moved_to_piece.setColour('r');
            destroyed_piece.setColour(' ');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            this->board[new_row-1][new_column-1] = destroyed_piece;
            this->no_black--;
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row-1][new_column+1].getColour() == 'b') {
            checkersPiece destroyed_piece = CheckersBoard::findPiece(new_row-1, new_column+1);
            piece.setColour(' ');
            moved_to_piece.setColour('r');
            destroyed_piece.setColour(' ');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            this->board[new_row-1][new_column+1] = destroyed_piece;
            this->no_black--;
            return true;
        }
    }

    else if (piece.getColour() == 'b') {
        if (piece.getRow()-1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' ') {
            piece.setColour(' ');
            moved_to_piece.setColour('b');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row+1][new_column-1].getColour() == 'r') {
            checkersPiece destroyed_piece = CheckersBoard::findPiece(new_row+1, new_column-1);
            piece.setColour(' ');
            moved_to_piece.setColour('b');
            destroyed_piece.setColour(' ');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            this->board[new_row+1][new_column-1] = destroyed_piece;
            this->no_red--;
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row+1][new_column+1].getColour() == 'r') {
            checkersPiece destroyed_piece = CheckersBoard::findPiece(new_row+1, new_column+1);
            piece.setColour(' ');
            moved_to_piece.setColour('b');
            destroyed_piece.setColour(' ');
            this->board[piece.getRow()][piece.getColumn()] = piece;
            this->board[new_row][new_column] = moved_to_piece;
            this->board[new_row+1][new_column+1] = destroyed_piece;
            this->no_red--;
            return true;
        }
    }
    return false;
}