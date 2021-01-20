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
        sf::Color(10, 65, 194), sf::Color(5, 50, 170)
    },

    // J_Shape
    {
        sf::Color(114, 203, 59), sf::Color(100, 190, 45)
    },

    // L_Shape
    {
        sf::Color(255, 213, 10), sf::Color(250, 200, 7)
    },

    // O_Shape
    {
        sf::Color(255, 151, 28), sf::Color(240, 135, 15)
    },

    // S_Shape
    {
        sf::Color(255, 50, 19), sf::Color(190, 20, 5)
    },

    // T_Shape
    {
        sf::Color(131, 50, 214), sf::Color(115, 45, 200)
    },

    // Z_Shape
    {
        sf::Color(20, 194, 188), sf::Color(10, 170, 170)
    }
};

#endif

// // array containing [fillColor, outlineColor]
// const sf::Color colorkey[7][2] = {
//     // I_Shape
//     {
//         sf::Color(3, 65, 174), sf::Color(0, 45, 150)
//     },

//     // J_Shape
//     {
//         sf::Color(114, 203, 59), sf::Color(95, 190, 45)
//     },

//     // L_Shape
//     {
//         sf::Color(255, 213, 0), sf::Color(235, 190, 0)
//     },

//     // O_Shape
//     {
//         sf::Color(255, 151, 28), sf::Color(235, 130, 10)
//     },

//     // S_Shape
//     {
//         sf::Color(255, 50, 19), sf::Color(235, 30, 5)
//     },

//     // T_Shape
//     {
//         sf::Color(91, 3, 174), sf::Color(65, 0, 150)
//     },

//     // Z_Shape
//     {
//         sf::Color(3, 174, 168), sf::Color(0, 150, 135)
//     }
// };

// // array containing [fillColor, outlineColor]
// const sf::Color colorkey[7][2] = {
//     // I_Shape
//     {
//         sf::Color(3, 65, 174), sf::Color(0, 55, 164)
//     },

//     // J_Shape
//     {
//         sf::Color(114, 203, 59), sf::Color(104, 193, 49)
//     },

//     // L_Shape
//     {
//         sf::Color(255, 213, 0), sf::Color(240, 200, 0)
//     },

//     // O_Shape
//     {
//         sf::Color(255, 151, 28), sf::Color(245, 141, 18)
//     },

//     // S_Shape
//     {
//         sf::Color(255, 50, 19), sf::Color(245, 40, 10)
//     },

//     // T_Shape
//     {
//         sf::Color(91, 3, 174), sf::Color(80, 0, 160)
//     },

//     // Z_Shape
//     {
//         sf::Color(3, 174, 168), sf::Color(0, 165, 150)
//     }
// };