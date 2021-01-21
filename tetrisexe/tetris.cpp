#include "tetris.hpp"

#include "gameinfo.hpp"

#include <iostream>
#include <math.h>

#include <unistd.h>

// path to the font
#define DISKOPIAPATH        "/home/pi/Documents/Games/Tetris/Assets/diskopia/DISKOPIA2.0.ttf"

#define FPSCAP              100

void drawStrings(
                    sf::RenderWindow &window,
                    int windowWidth, int windowHeight,
                    bool gameOver,
                    int lineCount, int score,
                    sf::Text &lineCountText, sf::Text &scoreText,
                    sf::Font &font
                    ) {
    
    if(gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(FONTSIZE * 1.5f);
            gameOverText.setString("Game Over!");
            gameOverText.setStyle(sf::Text::Bold);

            gameOverText.setOutlineThickness(4.0f);
            gameOverText.setFillColor(sf::Color::Black);
            gameOverText.setOutlineColor(sf::Color::White);

            gameOverText.setPosition(sf::Vector2f((float) windowWidth / 2.85f, (float) windowHeight/2));
            gameOverText.move(sf::Vector2f(
                                -gameOverText.getLocalBounds().width/2.0f,
                                -gameOverText.getLocalBounds().height
                                )
                            );
                            
            window.draw(gameOverText);
        }

    // turns the line count and score into strings then loads them into the text
    char lcString[16];
    sprintf(lcString, "%08d", lineCount);
    std::string lcS(lcString);

    lineCountText.setString(lcS);

    char scoreString[16];
    sprintf(scoreString, "%08d", score);
    std::string scS(scoreString);

    scoreText.setString(scS);

    // positions the linecount and score on the screen
    lineCountText.setPosition(sf::Vector2f((float) windowWidth / 2.85f, 0.0f));
    lineCountText.move(sf::Vector2f(-lineCountText.getLocalBounds().width/2.0f, (float) FONTSIZE * 0.8f));

    scoreText.setPosition(sf::Vector2f((float) windowWidth / 2.85f, (float) windowHeight));
    scoreText.move(sf::Vector2f(-scoreText.getLocalBounds().width/2.0f, (float) -FONTSIZE * 2.5f));

    window.draw(lineCountText);
    window.draw(scoreText);
}

int calculateScore(int linesCleared, int lineCount) {
    int scoreForClear;
    switch(linesCleared) {
        case 0 :    scoreForClear = 0;
                    break;

        case 1 :    scoreForClear = 40;
                    break;

        case 2 :    scoreForClear = 100;
                    break;

        case 3 :    scoreForClear = 300;
                    break;

        case 4 :    scoreForClear = 1200;
                    break;

        default :   scoreForClear = 1200 * linesCleared / 4;
                    break;
    }

    scoreForClear += lineCount;

    return scoreForClear;
}

int tetris(int startTime, int id, int numGames) {

    // setup window
    const int windowWidth = sf::VideoMode::getDesktopMode().width / numGames + numGames;// - 1;
    const int windowHeight = sf::VideoMode::getDesktopMode().height + 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris", sf::Style::None);
    window.setPosition(sf::Vector2i(windowWidth * id, -1));

    window.setFramerateLimit(FPSCAP);

    // setup game state
    int framesToDrop;
    int dropCounter = 0;

    int framesToMove = 10;
    int moveCounter = 0;

    int moveQueued = 0;

    int dropRate = 15;

    bool gameOver = false;

    int lineCount = 0;
    int score = 0;


    // loads the font
    // uses the native path of fonts on Raspberry Pi OS
    // swap this path to the path of your device, SFML does not do automatic path recognition
    sf::Font font;
    if (!font.loadFromFile(DISKOPIAPATH)) {
        std::cout << "font failed to load on process " << id << std::endl;
    }

    // setup the text
    sf::Text lineCountText;
    lineCountText.setFont(font);
    lineCountText.setCharacterSize(FONTSIZE);

    lineCountText.setOutlineThickness(2.0f);
    lineCountText.setFillColor(sf::Color::Black);
    lineCountText.setOutlineColor(sf::Color::White);


    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(FONTSIZE);

    scoreText.setOutlineThickness(2.0f);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setOutlineColor(sf::Color::White);

    sf::Text nextText;
    nextText.setFont(font);
    nextText.setCharacterSize(FONTSIZE);

    nextText.setOutlineThickness(4.0f);
    nextText.setFillColor(sf::Color::Black);
    nextText.setOutlineColor(sf::Color::White);
    nextText.setString("Next:");

    // setup controller
    // return -1 when the controller disconnects
    if(!sf::Joystick::isConnected(id)) {
        // return -1;
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
    const int matrixHeight = 3 * windowHeight / 4;
    const int matrixWidth = HEIGHTWIDTHRATIO * matrixHeight;

    int matrixX = (windowWidth - matrixWidth)/4;
    int matrixY = (windowHeight - matrixHeight)/2;

    // hack to make the 1 player games centered
    if(numGames == 1) {
        matrixX *= 2;
    }

    Matrix matrix(matrixX, matrixY, matrixWidth, matrixHeight);

    // setup rng and chose the next piece
    // startTime is used as the seed
    // startTime remains constant across instances of the game
    srand(startTime);

    int nextShape = rand()%NUMSHAPES;
    Piece piece((pieceShape) nextShape);

    nextShape = (pieceShape) rand()%NUMSHAPES;

    window.display();

    while(startTime > time(NULL)) {
        usleep(5);
    }
    std::cout << "Game starting... id: " << id << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // rotates pieces (once per key press)
            // happens on the same frame
            if(event.type == sf::Event::JoystickButtonPressed) {
                if(event.joystickButton.joystickId == (unsigned int) id) {
                    if(event.joystickButton.button == J_B) {
                        matrix.rotatePiece(piece, 1);
                    }

                    if(event.joystickButton.button == J_A) {
                        matrix.rotatePiece(piece, -1);
                    }

                    if(event.joystickButton.button == J_START) {
                        window.close();
                        // gameOver=true;
                    }
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

        if(gameOver) {
            continue;
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

                // drop the piece and deal with the outcome of the drop
                int linesCleared = matrix.dropPiece(piece);
                if(linesCleared >= 0) {
                    piece = Piece((pieceShape) nextShape);
                    nextShape = rand()%NUMSHAPES;

                    score += calculateScore(linesCleared, lineCount);

                    lineCount += linesCleared;
                }

                else if(linesCleared == -1) {
                    gameOver = true;
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

        matrix.draw(window, piece, (pieceShape) nextShape, nextText);

        // hack to make 1 player games line up the text
        int ww = windowWidth;
        if(numGames == 1) {
            ww *= 1.425f;
        }

        drawStrings(
            window,
            ww, windowHeight,
            gameOver,
            lineCount, score,
            lineCountText, scoreText,
            font
        );

        window.display();
    }

    return 0;
}