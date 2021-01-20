#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// path to the font
#define DISKOPIAPATH        "./Assets/diskopia/DISKOPIA2.0.ttf"

// number of options on the menu
#define NUMMENUITEMS        2

// the game waits this many seconds before starting
#define STARTDELAY          2

#define INTCHARBUFFERSIZE   1024
#define MAXPLAYERS          5

int startGames(int numGames) {

    // the seed is the start time of the game
    char seed[INTCHARBUFFERSIZE];

    // the game starts with a delay
    int startTime = time(NULL) + STARTDELAY;
    sprintf(seed, "%d",startTime);

    // string to hold the number of games
    char numGamesS[3];
    sprintf(numGamesS, "%d", numGames);

    for(int i = 0; i < numGames; i++) {
        char id[3];
        sprintf(id, "%d", i);

        switch(fork()) {
            case 0  :   execl("./tetrisexe/tetris", "tetris", seed, id, numGamesS, NULL);
                        break;

            default :   break;
        }
    }

    for(int i = 0; i < numGames; i++) {
        wait(NULL);
    }

    return 0;
}

int main(int argc, char *argv[]) {

    // set up the window
    const int windowWidth = sf::VideoMode::getDesktopMode().width + 1;
    const int windowHeight = sf::VideoMode::getDesktopMode().height + 1;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris Menu", sf::Style::None);
    window.setPosition(sf::Vector2i(-1, -1));

    window.setFramerateLimit(60);

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

    // loads the font
    // uses the native path of fonts on Raspberry Pi OS
    // swap this path to the path of your device, SFML does not do automatic path recognition
    sf::Font font;
    if (!font.loadFromFile(DISKOPIAPATH)) {
        std::cout << "font failed to load" << std::endl;
    }

    int titleTextSize = windowWidth/10;
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(titleTextSize);

    titleText.setString("Tetris");
    titleText.setStyle(sf::Text::Bold);

    titleText.setPosition(sf::Vector2f((float) windowWidth/2.0f, (float) windowHeight/4.0f));
    titleText.move(sf::Vector2f(-titleText.getLocalBounds().width/2.0f, 0.0f));

    titleText.setOutlineThickness(5.0f);
    titleText.setFillColor(sf::Color::Black);
    titleText.setOutlineColor(sf::Color::White);

    const int fontSize = windowWidth/30;

    sf::Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(fontSize);

    menuText.setOutlineThickness(2.0f);
    menuText.setFillColor(sf::Color::Black);
    menuText.setOutlineColor(sf::Color::White);

    sf::Text quitText;
    quitText.setFont(font);
    quitText.setCharacterSize(fontSize);

    quitText.setOutlineThickness(2.0f);
    quitText.setFillColor(sf::Color::Black);
    quitText.setOutlineColor(sf::Color::White);

    bool selectingNumPlayers = true;
    int numPlayers = 1;

    bool closeWindow = false;

    int menuSelection = 0;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // rotates pieces (once per key press)
            // happens on the same frame
            if(event.type == sf::Event::JoystickButtonPressed) {
                if(event.joystickButton.joystickId == 0) {
                    if(event.joystickButton.button == J_B) {
                        if(!selectingNumPlayers && menuSelection == 0) {
                            selectingNumPlayers = true;
                        }
                    }

                    if(event.joystickButton.button == J_A) {
                        if(menuSelection == 0) {
                            if(selectingNumPlayers) {
                                selectingNumPlayers = false;
                            }

                            else {
                                window.clear();
                                window.display();
                                startGames(numPlayers);

                                selectingNumPlayers = true;
                                numPlayers = 1;
                            }
                        }

                        else {
                            closeWindow = true;
                        }
                    }
                }
            }

            if(event.type == sf::Event::JoystickMoved) {
                int xDir = 0;

                if(menuSelection == 0 && selectingNumPlayers) {
                    float xInput = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

                    if(xInput > 0.5f) {
                        xDir = 1;
                    }

                    else if(xInput < -0.5f) {
                        xDir = -1;
                    }

                    // modular arithmetic...
                    // numPlayers bound to [1,MAXPLAYERS]
                    numPlayers = (numPlayers + xDir - 1 + MAXPLAYERS) % MAXPLAYERS + 1;   
                }

                // locks diagonal inputs

                if(xDir == 0) {
                    float yInput = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                    int yDir = 0;

                    if(yInput > 0.5f) {
                        yDir = 1;
                    }

                    else if(yInput < -0.5f) {
                        yDir = -1;
                    }

                    // more modular arithmetic
                    // menuSelection bound to [0,NUMMENUITEMS]
                    menuSelection = (menuSelection + yDir + NUMMENUITEMS) % NUMMENUITEMS;
                }
            }
        }

        if(closeWindow) {
            break;
        }

        std::string menuString;
        if(selectingNumPlayers) {
            if(menuSelection == 0) {
                menuString = "- " + std::to_string(numPlayers) + " -";
            }

            else {
                menuString = std::to_string(numPlayers);
            }
        }

        else {
            if(menuSelection == 0) {
                menuString = (std::string) "- Start Game -";
            }

            else {
                menuString = (std::string) "Start Game";
            }
        }

        std::string quitString;
        if(menuSelection == 0) {
            quitString = (std::string) "Quit";
        }

        else {
            quitString = (std::string) "- Quit -";
        }

        menuText.setString(menuString);
        menuText.setPosition(sf::Vector2f((float) windowWidth/2.0f, (float) windowHeight/2.0f));
        menuText.move(sf::Vector2f(-menuText.getLocalBounds().width/2.0f, (float) fontSize * 2.0f));

        quitText.setString(quitString);
        quitText.setPosition(sf::Vector2f((float) windowWidth/2.0f, (float) windowHeight/2.0f));
        quitText.move(sf::Vector2f(-quitText.getLocalBounds().width/2.0f, 0.0f));

        window.clear();

        window.draw(titleText);
        window.draw(menuText);
        window.draw(quitText);

        window.display();
    }

    if(window.isOpen()) {
        window.close();
    }

    return 0;
}

// cd /mnt/c/Users/aryag/OneDrive/Documents/GitHub/Tetris
// g++ SFMLTest.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system