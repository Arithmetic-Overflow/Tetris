#include "piece.hpp"

Piece::Piece(pieceShape shape) {
    this->shape = shape;

    // Spawning positions of the pieces
    this->xPos = (shape == P_I || shape == P_O) ? 
                    MATRIXWIDTH/2 - 2 :
                    MATRIXWIDTH/2 - 2;

    this->yPos = (shape == P_I) ?
                    MATRIXHEIGHT  + 0 :
                    MATRIXHEIGHT  + 1;

    // this->yPos -= 3;
    
    // Initial rotation of 0
    this->rotation = 0;

    // Load the shape of the piece into its cells
    this->cells = (int **) malloc(sizeof(int *) * DIM);

    for(int i = 0; i < DIM; i++) {
        this->cells[i] = (int *) malloc(sizeof(int) * DIM);

        for(int j = 0; j < DIM; j++) {
            this->cells[i][j] = shapeMap[shape][i][j];
        }
    }
}

// Piece::~Piece() {
//     for(int i = 0; i < DIM; i++) {
//         free(this->cells[i]);
//     }
// }

int Piece::getX() {
    return this->xPos;
}

int Piece::getY() {
    return this->yPos;
}

void Piece::move(int movedir) {
    this->xPos += movedir;
}

void Piece::drop() {
    this->yPos--;
}

void Piece::rotate(int rotdir) {
    // Pieces rotate in 90 degree intervals therefore
    // exactly 4 possiible rotations exist
    this->rotation = (this->rotation + rotdir) % 4;
}

pieceShape Piece::getShape() {
    return this->shape;
}

int **Piece::getCells() {
    return this->cells;
}

void Piece::nextTranslation(int &nextX, int &nextY) {
}

void Piece::nextRotation(int **&newCells) {
}