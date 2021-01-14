#include "matrix.hpp"

Matrix::Matrix(int x, int y, int w, int h) {

}

int Matrix::getWidth() {
    return this->width;
}

int Matrix::getHeight() {
    return this->height;
}

int **Matrix::getMatrix() {
    return this->matrix;
}

int Matrix::clearRows() {
    return 0;
}

int Matrix::movePiece(Piece, int) {
    return 0;
}

int Matrix::dropPiece(Piece) {
    return 0;
}

int Matrix::rotatePiece(Piece, int) {
    return 0;
}

void Matrix::drawCell(int, int, int) {

}

void Matrix::drawPiece(Piece piece) {

}

void Matrix::draw() {

}