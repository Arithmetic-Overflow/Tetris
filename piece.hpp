#ifndef PIECEHPP
#define PIECEHPP

#include "piecedata.hpp"

class Piece {
    private:
        pieceShape shape;
        int xPos;
        int yPos;

    public:
        Piece(pieceShape);

        pieceShape getShape();

        void move(int);
        void rotate(int);

        Piece nextTranslation(int);
        Piece nextRotation(int);

        // Should only be used to display the next piece
        void setPos(int, int);
};

#endif