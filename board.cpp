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

bool CheckersBoard::movePiece(checkersPiece piece, int new_row, int new_column, bool has_to_take) {
    checkersPiece moved_to_piece = CheckersBoard::findPiece(new_row, new_column);
    if (piece.getColour() == 'r') {
        if (!has_to_take && ((piece.getRow()+1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' ') ||
        (piece.getKing() && piece.getRow()-1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' '))) {
            finishMovement(piece, moved_to_piece, false, new_row, new_column, 'r', 0, 0);
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row-1][new_column-1].getColour() == 'b') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'r', new_row-1, new_column-1);
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row-1][new_column+1].getColour() == 'b') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'r', new_row-1, new_column+1);
            return true;
        }
        else if (piece.getKing() && moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row+1][new_column-1].getColour() == 'b') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'r', new_row+1, new_column-1);
            return true;
        }
        else if (piece.getKing() && moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row+1][new_column+1].getColour() == 'b') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'r', new_row+1, new_column+1);
            return true;
        }

    }

    else if (piece.getColour() == 'b') {
        if (!has_to_take && (piece.getRow()-1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' ' ||
        (piece.getRow()+1 == new_row && (piece.getColumn()+1 == new_column || piece.getColumn()-1 == new_column) && moved_to_piece.getColour() == ' '))) {
            finishMovement(piece, moved_to_piece, false, new_row, new_column, 'b', 0, 0);
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row+1][new_column-1].getColour() == 'r') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'b', new_row+1, new_column-1);
            return true;
        }
        else if (moved_to_piece.getColour() == ' ' && piece.getRow()-2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row+1][new_column+1].getColour() == 'r') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'b', new_row+1, new_column+1);
            return true;
        }
        else if (piece.getKing() && moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()+2 == new_column && this->board[new_row-1][new_column-1].getColour() == 'r') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'b', new_row-1, new_column-1);
            return true;
        }
        else if (piece.getKing() && moved_to_piece.getColour() == ' ' && piece.getRow()+2 == new_row && piece.getColumn()-2 == new_column && this->board[new_row-1][new_column+1].getColour() == 'r') {
            finishMovement(piece, moved_to_piece, true, new_row, new_column, 'b', new_row-1, new_column+1);
            return true;
        }
    }
    return false;
}

void CheckersBoard::finishMovement(checkersPiece piece, checkersPiece moved_to_piece, bool destroying_piece, int new_row, int new_column, char piece_colour, int destroyed_row, int destroyed_column) {
    if (destroying_piece) {
        checkersPiece destroyed_piece = CheckersBoard::findPiece(destroyed_row, destroyed_column);
        moved_to_piece.setColour(piece_colour);
        moved_to_piece.setKing(piece.getKing());
        piece.setColour(' ');
        piece.setKing(false);
        destroyed_piece.setColour(' ');
        destroyed_piece.setKing(false);
        this->board[piece.getRow()][piece.getColumn()] = piece;
        this->board[new_row][new_column] = moved_to_piece;
        this->board[destroyed_row][destroyed_column] = destroyed_piece;
        piece_colour == 'r' ? this->no_black-- : this->no_red--;
    }
    else {
        moved_to_piece.setColour(piece_colour);
        moved_to_piece.setKing(piece.getKing());
        piece.setColour(' ');
        piece.setKing(false);
        this->board[piece.getRow()][piece.getColumn()] = piece;
        this->board[new_row][new_column] = moved_to_piece;
    }
}

void CheckersBoard::checkForKing() {
    for (int y=0; y < 8; y++) {
        if (this->board[7][y].getColour() == 'r' && !this->board[7][y].getKing()) {
            checkersPiece king_piece = CheckersBoard::findPiece(7,y);
            king_piece.setKing(true);
            this->board[7][y] = king_piece;
        }
        if (this->board[0][y].getColour() == 'b' && !this->board[0][y].getKing()) {
            checkersPiece king_piece = CheckersBoard::findPiece(0,y);
            king_piece.setKing(true);
            this->board[0][y] = king_piece;
        }
    }
}