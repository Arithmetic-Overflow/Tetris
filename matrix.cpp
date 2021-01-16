#include "matrix.hpp"
#include <iostream>

#define CELLBORDER 4.0f
#define MATRIXBORDER 8.0f

Matrix::Matrix(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;

    this->cellW = w / MATRIXWIDTH;
    this->cellH = h / MATRIXHEIGHT;

    this->width = this->cellW * MATRIXWIDTH;
    this->height = this->cellH * MATRIXHEIGHT;

    this->matrix = (int **) malloc(sizeof(int *) * MATRIXHEIGHT);
    for(int i = 0; i < MATRIXHEIGHT; i++) {
        this->matrix[i] = (int *) malloc(sizeof(int) * MATRIXWIDTH);

        for(int j = 0; j < MATRIXWIDTH; j++) {
            this->matrix[i][j] = 0;
        }
    }

    // for(int i = 0; i < MATRIXWIDTH; i++) {
    //     this->matrix[0][i] = 2;
    // }

    // for(int i = 0; i < 15; i++) {
    //     this->matrix[1][i] = 2;
    // }

    // for(int i = 0; i < MATRIXHEIGHT; i++) {
    //     this->matrix[i][0] = 2;
    // }

    // std::cout << this->width << std::endl;
    // std::cout << this->height << std::endl;
    // std::cout << this->cellW << std::endl;
    // std::cout << this->cellH << std::endl;
}

// Matrix::~Matrix() {
//    for(int i = 0; i < MATRIXHEIGH; i++) {
//         free(this->matrix[i]);
//     }
// }

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

int Matrix::movePiece(Piece&, int) {
    return 0;
}

int Matrix::dropPiece(Piece& piece) {
    int pieceX = piece.getX();
    int pieceY = piece.getY();

    bool validDrop = true;

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            int cellY = pieceY - i;
            int cellX = pieceX + j;

            int nextY = cellY - 1;

            int **pieceCells = piece.getCells();
            if(pieceCells[i][j] != 0) {
                validDrop = validDrop && this->isFreeCell(cellX, nextY);
            }
        }
    }

    if(validDrop) {
        piece.drop();
        return 0;
    }

    return 1;
}

int Matrix::rotatePiece(Piece&, int) {
    return 0;
}

bool Matrix::isValidCell(int cellX, int cellY) {
    return (
        cellX >= 0 && cellX < MATRIXWIDTH &&
        cellY >= 0 && cellY < MATRIXHEIGHT
    );
}

bool Matrix::isFreeCell(int cellX, int cellY) {
    if(this->isValidCell(cellX, cellY)) {
        return (this->matrix[cellY][cellX] == 0);
    }

    return (
        cellY >= 0 &&
        cellX >= 0 &&
        cellX < MATRIXWIDTH
    );
}

void Matrix::drawPiece(sf::RenderWindow &window, Piece &piece) {
    int pieceX = piece.getX();
    int pieceY = piece.getY();

    int **pieceCells = piece.getCells();

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            int cellY = pieceY - i;
            int cellX = pieceX + j;

            if(this->isValidCell(cellX, cellY)) {
                this->drawCell(window, pieceY - i, pieceX + j, pieceCells[i][j]);
            }
        }
    }
}

void Matrix::drawCell(sf::RenderWindow &window, int i, int j, int colorValue) {
    if(colorValue == 0) {
        return;
    }

    colorValue--;

    int cellX = this->x + this->cellW * j;
    int cellY = this->y + this->cellH * (MATRIXHEIGHT - (i + 1));

    sf::RectangleShape cell(sf::Vector2f((float) this->cellW - 2*CELLBORDER, (float) this->cellH - 2*CELLBORDER));
    cell.move(sf::Vector2f((float) cellX,(float) cellY));

    cell.setOutlineThickness(-CELLBORDER);

    cell.setFillColor(colorkey[colorValue][0]);
    cell.setOutlineColor(colorkey[colorValue][1]);

    window.draw(cell);
}

void Matrix::drawOutline(sf::RenderWindow &window) {
    sf::RectangleShape outline(sf::Vector2f((float) this->width + 2*CELLBORDER, (float) this->height + 2*CELLBORDER));
    outline.move(sf::Vector2f((float) this->x - 2*CELLBORDER, (float) this->y - 2*CELLBORDER));

    outline.setOutlineThickness(MATRIXBORDER);

    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color(250, 250, 250));

    window.draw(outline);
}

void Matrix::drawMatrix(sf::RenderWindow &window) {
    for(int i = 0; i < MATRIXHEIGHT; i++) {
        for(int j = 0; j < MATRIXWIDTH; j++) {
            int cellValue = this->matrix[i][j];
            this->drawCell(window, i, j, cellValue);
        }
    }
}

void Matrix::draw(sf::RenderWindow &window, Piece &piece) {
    this->drawOutline(window);
    this->drawMatrix(window);
    this->drawPiece(window, piece);
}