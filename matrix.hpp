#ifndef MATRIXHPP
#define MATRIXHPP

#include "piece.hpp"
// #include "colorkey.hpp"

class Matrix {
    private:
        int width;
        int height;

        int **matrix;

        void drawCell(int, int, int);

        void drawPiece(Piece);

    public:
        Matrix(int, int, int, int);

        int getWidth();
        int getHeight();
        int **getMatrix();

        int clearRows();

        int movePiece(Piece, int);
        int dropPiece(Piece);
        int rotatePiece(Piece, int);

        void draw();
};

#endif