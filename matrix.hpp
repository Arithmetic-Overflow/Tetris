#ifndef MATRIXHPP
#define MATRIXHPP

#include "piece.hpp"

class Matrix {
    private:
        // coordinates of the top left corner 
        int x;
        int y;

        // dimensions of the matrix (board)
        int width;
        int height;

        // width and height of a single cell
        int cellW;
        int cellH;

        // contains the values of every cell
        // 0 for empty, a positive int if filled
        int **matrix;

        void drawCell(sf::RenderWindow&, int, int, int);
        void drawPiece(sf::RenderWindow&, Piece&);
        void drawOutline(sf::RenderWindow&);
        void drawMatrix(sf::RenderWindow&);

    public:
        Matrix(int, int, int, int);
        ~Matrix();

        int getWidth();
        int getHeight();
        int **getMatrix();

        int clearRows();

        int movePiece(Piece, int);
        int dropPiece(Piece);
        int rotatePiece(Piece, int);

        void draw(sf::RenderWindow&, Piece&);
};

#endif