#include "piece.hpp"

#include <iostream>

Piece::Piece(pieceShape shape) {
    this->shape = shape;

    this->xPos = (shape == P_I) ? MATRIXWIDTH/2 - 2 : MATRIXWIDTH/2 - 1;
    this->yPos = (shape == P_I) ? MATRIXHEIGHT  + 3 : MATRIXHEIGHT  + 2;

    this->rotation = 0;

    this->cells = (int **) malloc(sizeof(int *) * DIM);

    for(int i = 0; i < DIM; i++) {
        this->cells[i] = (int *) malloc(sizeof(int) * DIM);

        for(int j = 0; j < DIM; j++) {
            this->cells[i][j] = shapeMap[shape][i][j];
        }
    }
}

Piece::~Piece() {
    std::cout << "?P" << std::endl;

    for(int i = 0; i < DIM; i++) {
        free(this->cells[i]);
    }

    free(this->cells);
}

int Piece::getX() {
    return this->xPos;
}

int Piece::getY() {
    return this->yPos;
}

void Piece::move(int movedir) {
    this->xPos += movedir;
}

void Piece::rotate(int rotdir) {
    this->rotation = (this->rotation + rotdir) % 4;
}

pieceShape Piece::getShape() {
    return this->shape;
}

int **Piece::getCells() {
    return this->cells;
}

Piece Piece::nextTranslation(int movedir) {
    return *this;
}

Piece Piece::nextRotation(int rotdir) {
    return *this;
}