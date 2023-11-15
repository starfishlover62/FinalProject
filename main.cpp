#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "tank.h"
#include "bullet.h"
#include "enemies.h"

void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window);

int main()
{

    const float SCREEN_RES_X = 1000, SCREEN_RES_Y = 800;

    //granularity used to update the game
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/ 60.f);
    sf::Clock clock;
    //start the clock
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // output feedback for closed, paused, unpaused
    const bool OUTPUT_FEEDBACK = false;

    // create window of size 800 x 800 with title Space Invaders
    sf::RenderWindow window(sf::VideoMode(SCREEN_RES_X, SCREEN_RES_Y), "Space Invaders");
    // Enable vertical synchronization
    window.setVerticalSyncEnabled(true); // sync with system frame rate

    PlayerName playerName;
    
    // comment out to skip enter name screen
    //playerName.setPlayerName(window, OUTPUT_FEEDBACK);

    // check if the player's name is empty or contains only whitespace
    if(playerName.getPlayerName().find_first_not_of(" \t\n") == std::string::npos)
    {
        playerName.setPlayerName("No Name");
    }

    Gameboard gameboard(playerName.getPlayerName(), 0);

    Enemies aliens;
    
    //initialize tank
    Tank tankOne;

    // init lives as tank sprites
    Tank tankLife, tankLife2, tankLife3;
    tankLife.setOrigin(-580.f, 1485.f);
    float initialTankLifeScale = 0.5f; // Adjust this value as needed
    tankLife.setScale(initialTankLifeScale, initialTankLifeScale);
    
    //initialize friendly bullet
    Bullet tankBullet(true);
    
    //initialize ground
    sf::Texture gTexture;
    gTexture.loadFromFile("./assets/siground.png");
    sf::Sprite gSprite;
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(85, 465, SCREEN_RES_X, 4));
    gSprite.setOrigin(400.f, 2.f);
    gSprite.setPosition(sf::Vector2f(400.f, 777.f));

    bool friendlyBulletFired = false; //flag to check if friendly bullet is onscreen
    bool isSpaceReleased = true; //flag to check if spacebar has been released
    bool isLeftReleased = true; //flag to check if left arrow key has been released
    bool isRightReleased = true; //flag to check if right arrow key has been released
  
    bool paused = false; // flag for paused game
  
    sf::Text levelText = gameboard.getLevelText(); // level text
    levelText = gameboard.getLevelText(); // increment to level 1

    sf::Text pauseText = gameboard.getPauseText(); // pause text
    sf::Text gameOverText = gameboard.getGameOverText(); // game over text
    sf::Text quitText = gameboard.getCloseText(); // quit text

    sf::Text retryText = gameboard.getRetryText(); // retry text
    sf::Text livesText = gameboard.getLivesText(); // lives text

    int lives = 3; // start with three lives
    
    while (window.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // close was executed
            {
                quit(OUTPUT_FEEDBACK, quitText, window);
            }
            else if(event.type == sf::Event::KeyPressed) // a key was pressed
            {
                if(!paused)
                {
                    if (event.key.code == sf::Keyboard::Space) //set flag stating space key is held
                    {
                        isSpaceReleased = false;
                    }
                    else if (event.key.code == sf::Keyboard::Right) //set flag stating right arrow key is held
                    {
                        isRightReleased = false;
                    }
                    else if (event.key.code == sf::Keyboard::Left) //set flag stating left arrow key is held
                    {
                        isLeftReleased = false;
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        paused = !paused; // toggle pause state
                        isSpaceReleased = true;
                        isRightReleased = true;
                        isLeftReleased = true;

                        // unpause when player presses ENTER
                        while (paused)
                        {
                            window.draw(pauseText); // draw pause
                            window.display(); // display pause
                            if (event.type == sf::Event::Closed)
                            {
                                quit(OUTPUT_FEEDBACK, quitText, window);
                            }
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                                {
                                    paused = !paused; // unpause
                                    if(OUTPUT_FEEDBACK) std::cerr << "Unpaused\n"; // for debugging/feedback
                                }
                                else if(event.key.code == sf::Keyboard::Escape)
                                {
                                    quit(OUTPUT_FEEDBACK, quitText, window);
                                }
                            }
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        quit(OUTPUT_FEEDBACK, quitText, window);
                    }
                }
            }
            else if(event.type == sf::Event::KeyReleased) //a key was released
            {
                if(!paused)
                {
                    if (event.key.code == sf::Keyboard::Right) //set flag stating right arrow key is released
                    {
                        isRightReleased = true;
                    }
                    if (event.key.code == sf::Keyboard::Left) //set flag stating left arrow key is released
                    {
                        isLeftReleased = true;
                    }
                    if (event.key.code == sf::Keyboard::Space) //set flag stating space key is released
                    {
                        isSpaceReleased = true;
                    }
                }
            }
        }
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            window.clear();
            // draw name and score
            if(!paused){
                gameboard.draw(window);
                // draw squids
                aliens.draw(window);
                //draw tank
                window.draw(tankOne);
                // draw tank lives
                window.draw(tankLife);
                //draw friendly bullet, move bullet up until it leaves the visible screen
                window.draw(tankBullet);
                if (tankBullet.getLocation().y >=-4)
                {
                    tankBullet.moveBulletUp();
                }
                //loop to check if bullet is still on screen
                if (tankBullet.getLocation().y <= 0)
                {
                    friendlyBulletFired = false;
                }
                //loop that checks if friendly bullet collides with squid, if so moves bullet and squid offscreen and increments score. TODO: add death animation here
                //hitbox detection is off, unsure if we want to leave alien sprites origin drawn to top left or change to middle
                int val = aliens.checkCollision(&tankBullet);
                if(val != -1){
                    gameboard.increaseScore(val);
                }
                //loop to move tank right if right key has not been released
                if (isRightReleased == false)
                {
                    tankOne.moveTankRight(SCREEN_RES_X);
                }
                //loop to move tank left if left key has not been released
                if (isLeftReleased == false)
                {
                    tankOne.moveTankLeft();
                }
                //loop to shoot a bullet if space has not been released and no friendly bullets are on screen
                if (isSpaceReleased == false && friendlyBulletFired == false)
                {
                    //set friendly bullet to position of tank barrel
                    tankBullet.setLocation(tankOne.getLocation());
                    friendlyBulletFired = true;
                }
                //draw ground
                window.draw(levelText);
                window.draw(livesText);
                window.draw(gSprite);
                window.display();
            }
            else
            {
                window.draw(pauseText);
            }
        }
    }

    return 0;
}

void quit(bool OUTPUT_FEEDBACK, const sf::Text quitText, sf::RenderWindow& window)
{
    // for debugging/feedback
    if (OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
    
    window.draw(quitText);
    window.display();
    sf::sleep(sf::seconds(0));
    
    window.close();  // Close the window
}