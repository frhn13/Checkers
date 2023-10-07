class checkersPiece {
    bool is_king;
    char colour;
    bool is_alive;
    int row;
    int column;

    public:
        checkersPiece(char colour, bool is_alive, int row, int column, bool is_king);
        void setColour(char type);
        void setAlive(bool isAlive);
        void setKing(bool is_king);
        char getColour();
        int getRow();
        int getColumn();
        bool getKing();
};