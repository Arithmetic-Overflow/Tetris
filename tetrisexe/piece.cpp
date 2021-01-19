#include "piece.hpp"

#include <iostream>

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

bool Piece::isValidCell(int cellX, int cellY) {
    return (
        cellX >= 0 && cellX < DIM &&
        cellY >= 0 && cellY < DIM
    );
}

int Piece::getX() {
    return this->xPos;
}

int Piece::getY() {
    return this->yPos;
}

// moves a piece horizontally
void Piece::move(int movedir) {
    this->xPos += movedir;
}

// moves a piece down one block
void Piece::drop() {
    this->yPos--;
}

// loads the next rotation into rotatedCells
void Piece::generateRotation(int **rotatedCells, int rotdir) {

    // the O piece doesn't rotate
    if(this->shape == P_O) {
        for(int i = 0; i < DIM; i++) {
            for(int j = 0; j < DIM; j++) {
                rotatedCells[i][j] = this->cells[i][j];
            }
        }

        return;
    }

    // the I piece can only be vertical or horizontal
    if(this->shape == P_I) {
        rotdir = 1;
    }

    // centre of rotation
    int cx = 1;
    int cy = 1;

    // loop indices not labelled i and j
    // this is to avoid confusion with the imaginary number i
    for(int x = 0; x < DIM; x++) {
        for(int y = 0; y < DIM; y++) {
            int cellValue = this->cells[y][x];

            if(!cellValue) {
                continue;
            }

            // coordinates are treated as complex number x + yi
            // they are multiplied by i for a counter-clockwise rotation
            
            // x and y coordinates relative to the centre
            int relX = x - cx;
            int relY = y - cy;

            // multiplied by -i for a clockwise rotation [(i^3) = -i]
            if(rotdir == -1) {
                relX *= -1;
                relY *= -1;
            }

            int newX = -relY + cx;
            int newY =  relX + cy;

            if(this->isValidCell(newX, newY)) {
                rotatedCells[newY][newX] = cellValue;
            }
        }
    }

    // the 4x4 grid is big enough to hold the I pieces
    // but not big enough to rotate them without any losses
    // to counteract missing squares the edge cases are handled
    if(this->shape == P_I) {
        int filledCell = (int) P_I + 1;

        // there are 4 possible rotations
        int currentRotation = (this->rotation + rotdir) % 4;

        switch(currentRotation%2) {
            case    0:  rotatedCells[1][0] = filledCell;
                        rotatedCells[1][3] = filledCell;
                        break;

            case    1:  rotatedCells[0][1] = filledCell;
                        rotatedCells[3][1] = filledCell;
                        break;

            default  :  break;
        }
    }
}

// loads a list of cells into the current cells
void Piece::loadRotation(int **rotatedCells, int rotdir) {

    // identity used to keep this->rotation >= 0
    // the identity: (a+b)%b = a%b
    this->rotation = (this->rotation + rotdir + 4) % 4;

    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            this->cells[i][j] = rotatedCells[i][j];
        }
    }
}

pieceShape Piece::getShape() {
    return this->shape;
}

int **Piece::getCells() {
    return this->cells;
}