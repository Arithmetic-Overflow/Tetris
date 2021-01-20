#include "matrix.hpp"
#include <math.h>
#include <iostream>

#define CELLBORDERSCALE      1.0f / 8.0f
#define MATRIXBORDERSCALE    1.0f / 4.0f

Matrix::Matrix(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;

    this->cellW = w / MATRIXWIDTH;
    this->cellH = h / MATRIXHEIGHT;

    this->width = this->cellW * MATRIXWIDTH;
    this->height = this->cellH * MATRIXHEIGHT;

    // std::cout << this->cellW << " " << this->cellH << std::endl;

    this->cellBorder = floor(cellW * CELLBORDERSCALE);
    this->matrixBorder = floor(cellH * MATRIXBORDERSCALE);

    // a 2 dimensional array
    this->matrix = (int **) malloc(sizeof(int *) * MATRIXHEIGHT);
    for(int i = 0; i < MATRIXHEIGHT; i++) {
        this->matrix[i] = (int *) calloc(MATRIXWIDTH, sizeof(int));
    }
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

// moves down the matrix to delete cleared rows
void Matrix::moveDownRows(int clearedRow) {
    for(int i = clearedRow; i < MATRIXHEIGHT - 1; i++) {
        for(int j = 0; j < MATRIXWIDTH; j++) {
            this->matrix[i][j] = this->matrix[i+1][j];
        }
    }
}

// clears full rows
// is called whenever pieces embed onto the matrix
int Matrix::clearRows() {
    for(int i = 0; i < MATRIXHEIGHT; i++) {
        bool fullRow = true;

        for(int j = 0; j < MATRIXWIDTH; j++) {
            if(this->matrix[i][j] == 0) {
                fullRow = false;
                break;
            }
        }

        if(fullRow) {
            this->moveDownRows(i);
            i--;
        }
    }

    return 0;
}

// when a piece lands its data gets copied onto the matrix
// the cells will stay perpetually until removed
void Matrix::embedPiece(Piece& piece) {
    int pieceX = piece.getX();
    int pieceY = piece.getY();

    int **pieceCells = piece.getCells();

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            int cellY = pieceY - i;
            int cellX = pieceX + j;

            // set the cells the piece lands on to be filled
            if(this->isValidCell(cellX, cellY)) {
                // if(this->matrix[cellY][cellX] == 0) {
                //     this->matrix[cellY][cellX] = pieceCells[i][j];
                // }

                // either the matrix or pieceCells at that point should be 0
                this->matrix[cellY][cellX] |= pieceCells[i][j];
            }
        }
    }

    this->clearRows();
}

// attempts to move a piece
// returns 0 for success and 1 for failure
int Matrix::movePiece(Piece& piece, int movedir) {
    int pieceX = piece.getX();
    int pieceY = piece.getY();

    int **pieceCells = piece.getCells();

    bool validMove = true;

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            int cellY = pieceY - i;
            int cellX = pieceX + j;

            int nextX = cellX + movedir;

            if(pieceCells[i][j] != 0) {
                validMove = validMove && this->isFreeCell(nextX, cellY);
            }
        }
    }

    if(validMove) {
        piece.move(movedir);
        return 0;
    }

    return 1;
}

// attempt to drop a piece
// if the piece has collided with something embed it in place
// returns 1 if the piece has collided with something
// returns 0 if it has successfully dropped
// returns -1 if the drop results in game over
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

    this->embedPiece(piece);

    return 1;
}

// attempts to rotate a piece in a specific direction
// returns 1 for failure and 0 for success
int Matrix::rotatePiece(Piece& piece, int rotdir) {

    // allocate memory to hold the rotated piece's info
    int **rotatedCells = (int **) malloc(sizeof(int *) * DIM);
    for(int i = 0; i < DIM; i++) {
        rotatedCells[i] = (int *) calloc(DIM, sizeof(int));
    }

    piece.generateRotation(rotatedCells, rotdir);

    int pieceX = piece.getX();
    int pieceY = piece.getY();

    bool validSpin = true;

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            validSpin = validSpin && this->isFreeCell(pieceX + i, pieceY - j);
        }
    }
    
    if(validSpin) {
        piece.loadRotation(rotatedCells, rotdir);
    }

    // deallocate rotatedCells
    for(int i = 0; i < DIM; i++) {
        free(rotatedCells[i]);
    }

    free(rotatedCells);

    return (int) validSpin;
}

// returns if the cell is a valid cell on the matrix
bool Matrix::isValidCell(int cellX, int cellY) {
    return (
        cellX >= 0 && cellX < MATRIXWIDTH &&
        cellY >= 0 && cellY < MATRIXHEIGHT
    );
}

// return if the cell is a valid cell and is free
bool Matrix::isFreeCell(int cellX, int cellY) {
    if(this->isValidCell(cellX, cellY)) {
        return this->matrix[cellY][cellX] == 0;
    }

    return (
        cellY >= 0 &&
        cellX >= 0 &&
        cellX < MATRIXWIDTH
    );
}

// draws the piece onto the window
// calls drawCell where the piece has active cells
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

    sf::RectangleShape cell(sf::Vector2f((float) this->cellW - 2*this->cellBorder, (float) this->cellH - 2*this->cellBorder));
    cell.move(sf::Vector2f((float) cellX,(float) cellY));

    cell.setOutlineThickness(-this->cellBorder);

    cell.setFillColor(colorkey[colorValue][0]);
    cell.setOutlineColor(colorkey[colorValue][1]);

    window.draw(cell);
}

// draws the bounding box for the matrix
void Matrix::drawOutline(sf::RenderWindow &window) {
    sf::RectangleShape outline(sf::Vector2f((float) this->width + 2*this->cellBorder, (float) this->height + 2*this->cellBorder));
    outline.move(sf::Vector2f((float) this->x - 2*this->cellBorder, (float) this->y - 2*this->cellBorder));

    outline.setOutlineThickness(this->matrixBorder);

    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color(250, 250, 250));

    window.draw(outline);
}

// draws each cell of the matrix
void Matrix::drawMatrix(sf::RenderWindow &window) {
    for(int i = 0; i < MATRIXHEIGHT; i++) {
        for(int j = 0; j < MATRIXWIDTH; j++) {
            int cellValue = this->matrix[i][j];
            this->drawCell(window, i, j, cellValue);
        }
    }
}

// draws everything on and around the matrix
// also responsible for the "next box"
void Matrix::draw(sf::RenderWindow &window, Piece &piece) {
    this->drawOutline(window);
    this->drawMatrix(window);
    this->drawPiece(window, piece);
}