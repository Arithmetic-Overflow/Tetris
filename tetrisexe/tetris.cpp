#include "tetris.hpp"

#include "gameinfo.hpp"

#include <iostream>
#include <math.h>

#define FPSCAP      100

int tetris(int seed, int id) {

    // setup window
    const int windowWidth = sf::VideoMode::getDesktopMode().width / 2 + 1;
    const int windowHeight = sf::VideoMode::getDesktopMode().height + 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetriis", sf::Style::None);
    window.setPosition(sf::Vector2i(windowWidth * id, -1));

    window.setFramerateLimit(FPSCAP);

    // setup 
    int framesToDrop;
    int dropCounter = 0;

    int framesToMove = 10;
    int moveCounter = 0;

    int moveQueued = 0;

    int dropRate = 15;


    // loads the font
    // uses the native path of fonts on Raspberry Pi OS
    // swap this path to the path of your device, SFML does not do automatic path recognition
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/quicksand/Quicksand-Regular.ttf")) {
        std::cout << "font failed to load" << std::endl;
    }

    // sf::Text frameCountText;
    // frameCountText.setFont(font);
    // frameCountText.setCharacterSize(50);
    // frameCountText.move(sf::Vector2f(50.0f, 50.0f));

    // setup controller
    if(!sf::Joystick::isConnected(id)) {
        return -1;
    }

    // easy access to the buttons of the SNES USB joystick (for RPi4)
    enum joystickButton {
        J_X         = 0,
        J_A         = 1,
        J_B         = 2,
        J_Y         = 3,
        J_LB        = 4,
        J_RB        = 5,
        J_SELECT    = 8,
        J_START     = 9
    };

    // setup clock and frame management
    int frameCount = 1;

    sf::Clock clock;
    float dt = 0.0f;

    // setup play matrix
    const int matrixHeight = 8 * windowHeight / 10;
    const int matrixWidth = HEIGHTWIDTHRATIO * matrixHeight;
    Matrix matrix((windowWidth - matrixWidth)/2, (windowHeight - matrixHeight)/2, matrixWidth, matrixHeight);


    // setup rng and chose the next piece
    srand(seed);

    int nextShape = rand()%NUMSHAPES;
    Piece piece((pieceShape) nextShape);

    nextShape = (pieceShape) rand()%NUMSHAPES;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // rotates pieces (once per key press)
            // happens on the same frame
            if(event.type == sf::Event::JoystickButtonPressed) {
                if(event.key.code == sf::Joystick::isButtonPressed(id, J_B)) {
                    matrix.rotatePiece(piece, 1);
                }

                if(event.key.code == sf::Joystick::isButtonPressed(id, J_A)) {
                    matrix.rotatePiece(piece, -1);
                }
            }

            // queues a move input
            // if the move is done on the same frame movement is jerky
            // the move is queued so it's responsive while remaining consistent
            if(event.type == sf::Event::JoystickMoved) {
                float xInput = sf::Joystick::getAxisPosition(id, sf::Joystick::X);
                if(xInput > 0.5f || xInput < -0.5f) {
                    moveQueued = (xInput > 0) ? 1: -1;
                }
            }
        }

        // drops pieces quicker if S is pressed
        framesToDrop = sf::Joystick::getAxisPosition(id, sf::Joystick::Y) > 0 ? dropRate/3 : dropRate;

        // increment the clock, only check for actions every frane
        dt += clock.restart().asSeconds();
        if(dt < TIMEPERFRAME) {
            continue;
        }

        // a while loop is favoured over an if statement
        // if the game's framerate suddenly drops the timings remain consistent
        // if the while is replaced with an if, the game will freeze after drops in framerate
        // it will then attempt to catch up, causing an unstable framerate
        while(dt >= TIMEPERFRAME) {
            dt = std::fmod(dt, TIMEPERFRAME);
            frameCount++;

            // drops pieces
            dropCounter = (dropCounter + 1) % framesToDrop;
            if(dropCounter == 0) {
                if(matrix.dropPiece(piece)) {
                    piece = Piece((pieceShape) nextShape);

                    nextShape = rand()%NUMSHAPES;
                }
            }

            // moves pieces if there is a joystick input
            moveCounter = (moveCounter + 1) % framesToMove;
            if(moveCounter == 0) {
                if(moveQueued != 0) {
                    matrix.movePiece(piece, moveQueued);

                    moveQueued = 0;
                }

                else if(sf::Joystick::getAxisPosition(id, sf::Joystick::X) > 0) {
                    matrix.movePiece(piece, 1);
                }

                else if(sf::Joystick::getAxisPosition(id, sf::Joystick::X) < 0) {
                    matrix.movePiece(piece, -1);
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