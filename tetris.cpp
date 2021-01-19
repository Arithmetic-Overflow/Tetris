#include "tetris.hpp"

#include "gameinfo.hpp"

#include <iostream>
#include <math.h>

#define FPSCAP 72

int tetris() {
    const int windowWidth = sf::VideoMode::getDesktopMode().width   + 1;
    const int windowHeight = sf::VideoMode::getDesktopMode().height + 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetriis", sf::Style::None);
    window.setPosition(sf::Vector2i(0,0));

    window.setFramerateLimit(FPSCAP);

    int framesToDrop;
    int dropCounter = 0;

    int framesToMove = 6;
    int moveCounter = 0;

    const int matrixHeight = 8 * windowHeight / 10;
    const int matrixWidth = HEIGHTWIDTHRATIO * matrixHeight;

    // sf::Font font;
    // if (!font.loadFromFile("/usr/share/fonts/truetype/quicksand/Quicksand-Regular.ttf")) {
    //     std::cout << "font failed to load" << std::endl;
    // }

    // sf::Text frameCountText;
    // frameCountText.setFont(font);
    // frameCountText.setCharacterSize(50);
    // frameCountText.move(sf::Vector2f(50.0f, 50.0f));

    int frameCount = 1;

    sf::Clock clock;
    float dt = 0.0f;

    Matrix matrix((windowWidth - matrixWidth)/2, (windowHeight - matrixHeight)/2, matrixWidth, matrixHeight);
    int pp = 0;
    Piece piece((pieceShape) pp);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // rotates pieces (once per key press)
            if(event.type == sf::Event::EventType::KeyPressed) {
                if(event.key.code == sf::Keyboard::Q) {
                    matrix.rotatePiece(piece, 1);
                }

                if(event.key.code == sf::Keyboard::E) {
                    matrix.rotatePiece(piece, -1);
                }
            }
        }

        // drops pieces quicker if S is pressed
        framesToDrop = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? 15/3 : 15;

        dt += clock.restart().asSeconds();
        if(dt < TIMEPERFRAME) {
            continue;
        }

        while(dt >= TIMEPERFRAME) {
            dt = std::fmod(dt, TIMEPERFRAME);
            frameCount++;

            // drops pieces
            dropCounter = (dropCounter + 1) % framesToDrop;
            if(dropCounter == 0) {
                if(matrix.dropPiece(piece)) {
                    pp++;
                    pp%=NUMSHAPES;
                    piece = Piece((pieceShape) pp);
                }
            }

            // moves pieces
            moveCounter = (moveCounter + 1) % framesToMove;
            if(moveCounter == 0) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    matrix.movePiece(piece, 1);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    matrix.movePiece(piece, -1);
                    // piece.rotate(1);
                }
            }
        }

        window.clear();
        // frameCountText.setString(std::to_string(dropCounter));
        // window.draw(frameCountText);
        matrix.draw(window, piece);
        window.display();
    }

    return 0;
}