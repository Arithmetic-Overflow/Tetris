#include "tetris.hpp"

#include "gameinfo.hpp"

#include <iostream>
#include <math.h>

#define FPSCAP 72

int tetris() {
    const int windowWidth = sf::VideoMode::getDesktopMode().width   + 1;
    const int windowHeight = sf::VideoMode::getDesktopMode().height + 1;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris", sf::Style::None);
    window.setPosition(sf::Vector2i(0,0));
    window.setFramerateLimit(FPSCAP);

    int framesToDrop = 15;
    int dropCounter = 0;

    const int matrixHeight = 8 * windowHeight / 10;
    const int matrixWidth = HEIGHTWIDTHRATIO * matrixHeight;

    sf::RectangleShape matrixShape(sf::Vector2f(matrixWidth, matrixHeight));
    matrixShape.move(sf::Vector2f((windowWidth - matrixWidth)/2, (windowHeight - matrixHeight)/2));

    matrixShape.setFillColor(sf::Color::Transparent);
    matrixShape.setOutlineColor(sf::Color(250, 250, 250));
    matrixShape.setOutlineThickness(1.0f);

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
    Piece piece((pieceShape) 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                std::cout << "!!" << std::endl;
                window.close();
                std::cout << "!!" << std::endl;
            }
        }

        dt += clock.restart().asSeconds();
        if(dt < TIMEPERFRAME) {
            continue;
        }

        dt = std::fmod(dt, TIMEPERFRAME);
        frameCount++;
        dropCounter = (dropCounter + 1) % framesToDrop;

        if(dropCounter == 0) {
            
        }

        window.clear();
        // window.draw(matrixShape);
        // frameCountText.setString(std::to_string(dropCounter));
        // window.draw(frameCountText);
        matrix.draw(window, piece);
        window.display();
    }

    // std::cout << "?" << std::endl;

    return 0;
}