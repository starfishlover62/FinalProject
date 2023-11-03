#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "squid.h"
#include "tank.h"

int main()
{
    // output feedback for closed, paused, unpaused
    const bool OUTPUT_FEEDBACK = true;

    // create window of size 800 x 800 with title Space Invaders
    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders");

    PlayerName playerName;
    
    // comment out to skip enter name screen
    //playerName.setPlayerName(window);

    Gameboard gameboard(playerName.getPlayerName(), 0);

    const int Number_Of_Squids = 11;
    sf::Vector2f squidPositions[Number_Of_Squids];

    // initialize squids objects'
    for(int i = 0; i < Number_Of_Squids; i++)
    {
        squidPositions[i] = sf::Vector2f(i * 70 + 25, 150);
    }

    Squid squidObjects[Number_Of_Squids];

    // assign squid objects' position
    for (int i = 0; i < Number_Of_Squids; i++)
    {
        squidObjects[i].setTexture();
        squidObjects[i].setLocation(squidPositions[i]); // set position
    }

    //initialize tank
    Tank tankOne;

    //initialize ground
    sf::Texture gTexture;
    gTexture.loadFromFile("./assets/siground.png");
    sf::Sprite gSprite;
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(85, 465, 800, 4));
    gSprite.setOrigin(400.f, 2.f);
    gSprite.setPosition(sf::Vector2f(400.f, 777.f));

    
    // flag for paused game
    bool paused = false;

    while (window.isOpen())
    {
        sf::Text text;
        text.setString("Hello, SFML!");
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // close was executed
            {
                // for debugging/feedback
                if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                exit(0);
                break;
            }
            else if (event.type == sf::Event::MouseButtonPressed) // a click was made
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // TEST
                    gameboard.increaseScore(2);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // increment score with left click
                    gameboard.increaseScore(5);
                }
                else if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    // increment score with left click
                    gameboard.increaseScore(10);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(20);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(50);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(750);
                }
            }
            else if(event.type == sf::Event::KeyPressed) // a key was pressed
            {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    tankOne.moveTankRight();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    tankOne.moveTankLeft();
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    paused = !paused; // toggle pause state

                    // for debugging/feedback
                    if(OUTPUT_FEEDBACK) std::cerr << "Paused\n";

                    // unpause when player presses ENTER
                    while (paused)
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            // for debugging/feedback
                            if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                            window.close();
                            exit(0);
                        }
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                            {
                                paused = !paused; // unpause
                                // for debugging/feedback
                                if(OUTPUT_FEEDBACK) std::cerr << "Unpaused\n";
                            }
                            else if(event.key.code == sf::Keyboard::Escape)
                            {
                                // for debugging/feedback
                                if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                                window.close();
                                exit(0);
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    // for debugging/feedback
                    if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                    window.close();
                    exit(0);
                }
            }
        }

        window.clear();
        // draw name and score
        gameboard.draw(window);
        // draw squids
        for(int i = 0; i < Number_Of_Squids; i++)
        {
            window.draw(squidObjects[i]);
        }
        //draw tank
        window.draw(tankOne);
        //draw ground
        window.draw(gSprite);
        window.display();
    }

    return 0;
}
