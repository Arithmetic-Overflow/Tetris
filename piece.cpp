#include "piece.hpp"

Piece::Piece(pieceShape shape) {
    this->shape = shape;
}

void Piece::move(int) {

}

void Piece::rotate(int) {

}

pieceShape Piece::getShape() {
    return this->shape;
}

Piece Piece::nextTranslation(int movedir) {
    return *this;
}

Piece Piece::nextRotation(int rotdir) {
    return *this;
}