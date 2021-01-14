#ifndef PIECESHAPEDATAHPP
#define PIECESHAPEDATAHPP

#include <SFML/Graphics.hpp>

#define DIM 5
#define NUMSHAPES 7

const int shapeMap[NUMSHAPES][DIM][DIM] = {
    // I_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // J_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // L_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // O_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // S_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // T_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    },

    // Z_Shape
    {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
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
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // J_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // L_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // O_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // S_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // T_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    },

    // Z_Shape
    {
        sf::Color(250, 250, 250), sf::Color(220, 220, 220)
    }
};

#endif