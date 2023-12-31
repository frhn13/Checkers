#include "checkersPiece.hpp"
#include <vector>

class CheckersBoard {
    std::vector<std::vector<checkersPiece>> board;
    int no_red;
    int no_black;
    public:
        CheckersBoard();
        std::vector<std::vector<checkersPiece>> createBoard();
        std::vector<std::vector<checkersPiece>> getBoard();
        int getRed();
        int getBlack();
        void decreaseRed();
        void decreaseBlack();
        checkersPiece findPiece(int row, int column);
        bool checkPiece(int row, int column, char turn);
        bool movePiece(checkersPiece piece, int new_row, int new_column, bool has_to_take);
        void finishMovement(checkersPiece piece, checkersPiece moved_to_piece, bool destroying_piece, int new_row, int new_column, char piece_colour, int destroyed_row, int destroyed_column);
        void checkForKing();
};