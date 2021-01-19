#include "tetris.hpp"

int main(int argc, char *argv[]) {
    int seed = atoi(argv[1]);
    int id = atoi(argv[2]);
    return tetris(seed, id);
}

// cd /mnt/c/Users/aryag/OneDrive/Documents/GitHub/Tetris
// g++ SFMLTest..cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system