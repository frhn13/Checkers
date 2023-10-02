#include "checkersPiece.hpp"

checkersPiece::checkersPiece(char colour, bool is_alive, int row, int column, bool is_king) {
    this->colour = colour;
    this->is_alive = is_alive;
    this->row = row;
    this->column = column;
    this->is_king = is_king;
}

void checkersPiece::setColour(char type) {
    this->colour = type;
}

void checkersPiece::setAlive(bool isAlive) {
    this->is_alive = isAlive;
}

char checkersPiece::getColour() {
    return this->colour;
}