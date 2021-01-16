#ifndef PIECEHPP
#define PIECEHPP

#include "gameinfo.hpp"

#define ROTCENTRE {2, 2}

class Piece {
    private:
        pieceShape shape;
        int xPos;
        int yPos;
        int **cells;
        int rotation;

    public:
        Piece(pieceShape);
        // ~Piece();

        pieceShape getShape();
        int **getCells();

        int getX();
        int getY();

        void move(int);
        void fall();
        void rotate(int);

        void nextTranslation(int&, int&);
        void nextRotation(int**&);

        // Should only be used to display the next piece
        void setPos(int, int);

        Piece copy();
};

#endif