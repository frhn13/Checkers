#include "checkersPiece.hpp"
#include <vector>

class CheckersBoard {
    std::vector<std::vector<checkersPiece>> board;
    public:
        std::vector<std::vector<checkersPiece>> createBoard();
};