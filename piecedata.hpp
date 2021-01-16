#ifndef PIECESHAPEDATAHPP
#define PIECESHAPEDATAHPP

#include <SFML/Graphics.hpp>

#define DIM 4
#define NUMSHAPES 7

const int shapeMap[NUMSHAPES][DIM][DIM] = {
    // I_Shape
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },

    // J_Shape
    {
        {2,0,0,0},
        {2,2,2,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // L_Shape
    {
        {0,0,3,0},
        {3,3,3,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // O_Shape
    {
        {0,4,4,0},
        {0,4,4,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // S_Shape
    {
        {0,5,5,0},
        {5,5,0,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // T_Shape
    {
        {0,6,0,0},
        {6,6,6,0},
        {0,0,0,0},
        {0,0,0,0}
    },

    // Z_Shape
    {
        {7,7,0,0},
        {0,7,7,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

enum pieceShape {
    P_I,
    P_J,
    P_L,
    P_O,
    P_S,
    P_T,
    P_Z
};

// array containing [fillColor, outlineColor]
const sf::Color colorkey[7][2] = {
    // I_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // J_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // L_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // O_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // S_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // T_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    },

    // Z_Shape
    {
        sf::Color(250, 250, 250), sf::Color(200, 200, 200)
    }
};

#endif