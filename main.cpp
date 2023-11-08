#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "tank.h"
#include "bullet.h"
#include "enemies.h"

int main()
{
    // output feedback for closed, paused, unpaused
    const bool OUTPUT_FEEDBACK = true;

    // create window of size 800 x 800 with title Space Invaders
    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders");

    PlayerName playerName;

    Enemies aliens; // The formation of aliens
    
    // comment out to skip enter name screen
    //playerName.setPlayerName(window);

    Gameboard gameboard(playerName.getPlayerName(), 0);

    const int Number_Of_Squids = 11;
    sf::Vector2f squidPositions[Number_Of_Squids];

    //initialize tank
    Tank tankOne;
    //initialize firendly bullet
    Bullet tankBullet(true);

    //initialize ground
    sf::Texture gTexture;
    gTexture.loadFromFile("./assets/siground.png");
    sf::Sprite gSprite;
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(85, 465, 800, 4));
    gSprite.setOrigin(400.f, 2.f);
    gSprite.setPosition(sf::Vector2f(400.f, 777.f));
    
    bool paused = false; // flag for paused game
    sf::Text levelText = gameboard.levelText(); // level text
    sf::Text pauseText = gameboard.pauseText(); // pause text
    sf::Text gameOverText = gameboard.gameOverText(); // game over text
    sf::Text quitText = gameboard.quitText(); // quit text

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // close was executed
            {
                // for debugging/feedback
                if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                window.draw(quitText);
                window.close();
                // exit(0);
                // break;
            }
            else if (event.type == sf::Event::MouseButtonPressed) // a click was made
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // left click
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // right click
                }
                else if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    // middle click
                }
            }
            else if(event.type == sf::Event::KeyPressed) // a key was pressed
            {
                if (!paused && event.key.code == sf::Keyboard::Space)
                {
                    //if space is pressed, set friendly bullet to position of tank barrel
                    tankBullet.setLocation(tankOne.getLocation());
                }
                else if (!paused && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    tankOne.moveTankRight();
                }
                else if (!paused && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    tankOne.moveTankLeft();
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    paused = !paused; // toggle pause state

                    // for debugging/feedback
                    if(OUTPUT_FEEDBACK) std::cerr << "Paused/Unpaused\n";
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    // for debugging/feedback
                    if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
                    window.draw(quitText);
                    window.close();
                }
            }
        }
        if(window.isOpen()){ // Updating only occurs if the window is open
            if(!paused){ // Updating nearly everything only occurs if the game is not paused
                window.clear();
                // draw name and score
                gameboard.draw(window);

                aliens.draw(window); // Draws the screen of aliens

                //draw tank
                window.draw(tankOne);
                //draw friendly bullet, move bullet up until it leaves the visible screen
                window.draw(tankBullet);
                if (tankBullet.getLocation().y >= -1)
                {
                    tankBullet.moveBulletUp();
                }
                //loop that checks if friendly bullet collides with squid, if so moves bullet and squid offscreen and increments score. TODO: add death animation here
                //hitbox detection is off, unsure if we want to leave alien sprites origin drawn to top left or change to middle

                int val = aliens.checkCollision(&tankBullet); // aliens.checkCollision returns the score of the alien destroyed, otherwise -1
                if(val != -1){ // Updates score based on what was shot
                    gameboard.increaseScore(val);
                }
                
                //draw ground
                window.draw(gSprite);
            } else { // If the game is paused, draws the paused text
                window.draw(pauseText); // draw pause
            }
            window.display();
        }
    }
    return 0;
}
