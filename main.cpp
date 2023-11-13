#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "playerName.h"
#include "gameboard.h"
#include "alien.h"
#include "tank.h"
#include "bullet.h"

void quit(bool OUTPUT_FEEDBACK, sf::Text quitText, sf::RenderWindow& window);

int main()
{
    //granularity used to update the game
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/ 60.f);
    sf::Clock clock;
    //start the clock
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // output feedback for closed, paused, unpaused
    const bool OUTPUT_FEEDBACK = false;

    // create window of size 800 x 800 with title Space Invaders
    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders");

    PlayerName playerName;
    
    // comment out to skip enter name screen
    //playerName.setPlayerName(window);

    Gameboard gameboard(playerName.getPlayerName(), 0);

    // create and assign squid objects
    const int Number_Of_Squids = 11;
    sf::Vector2f squidPosition[Number_Of_Squids];

    // initialize squids objects
    for(int i = 0; i < Number_Of_Squids; i++)
    {
        squidPosition[i] = sf::Vector2f(i * 70 + 25, 150);
    }
    Squid squidObjects[Number_Of_Squids];
    // assign squid objects position
    for (int i = 0; i < Number_Of_Squids; i++)
    {
        squidObjects[i].setLocation(squidPosition[i]); // set position
    }
    // create and assign crab objects
    const int Number_Of_Crabs = 11;
    sf::Vector2f crabPosition[Number_Of_Crabs];

    // initialize crab objects
    for(int i = 0; i < Number_Of_Crabs; i++)
    {
        crabPosition[i] = sf::Vector2f(i * 70 + 25, 250);
    }
    Crab crabObjects[Number_Of_Crabs];
    // assign crab objects position
    for (int i = 0; i < Number_Of_Crabs; i++)
    {
        crabObjects[i].setLocation(crabPosition[i]); // set position
    }

    // create and assign jellyfish objects
    const int Number_Of_Jellyfish = 11;
    sf::Vector2f jellyfishPosition[Number_Of_Jellyfish];
    // initialize jellyfish objects
    for(int i = 0; i < Number_Of_Jellyfish; i++)
    {
        jellyfishPosition[i] = sf::Vector2f(i * 70 + 25, 350);
    }
    Jellyfish jellyfishObjects[Number_Of_Jellyfish];
    // assign jellyfish objects position
    for (int i = 0; i < Number_Of_Jellyfish; i++)
    {
        jellyfishObjects[i].setLocation(jellyfishPosition[i]); // set position
    }

    //initialize tank
    Tank tankOne;
    //initialize friendly bullet
    Bullet tankBullet(true);

    //initialize ground
    sf::Texture gTexture;
    gTexture.loadFromFile("./assets/siground.png");
    sf::Sprite gSprite;
    gSprite.setTexture(gTexture);
    gSprite.setTextureRect(sf::IntRect(85, 465, 900, 4));
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

                    // for debugging/feedback
                    if(OUTPUT_FEEDBACK) std::cerr << "Paused\n";

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
                else if (event.key.code == sf::Keyboard::Escape) // escape key was pressed
                {
                    quit(OUTPUT_FEEDBACK, quitText, window);
                }
            }
            else if(event.type == sf::Event::KeyReleased) //a key was released
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
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            window.clear();
            // draw name and score
            gameboard.draw(window);
            // draw squids
            for(int i = 0; i < Number_Of_Squids; i++)
            {
                window.draw(squidObjects[i]);
            }
            // draw crabs
            for(int i = 0; i < Number_Of_Squids; i++)
            {
                window.draw(crabObjects[i]);
            }
            // draw jellyfish
            for(int i = 0; i < Number_Of_Squids; i++)
            {
                window.draw(jellyfishObjects[i]);
            }
            //draw tank
            window.draw(tankOne);
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
            for(int i = 0; i< Number_Of_Squids; i++)
            {
                if (tankBullet.getLocation().y == squidObjects[i].getLocation().y && tankBullet.getLocation().x >= (squidObjects[i].getLocation().x -40.f) && tankBullet.getLocation().x <= (squidObjects[i].getLocation().x +40.f))
                {
                    tankBullet.setLocation({-200, -200});
                    squidObjects[i].setLocation({-100, -100});
                    gameboard.increaseScore(40);
                }
            }
            //loop to move tank right if right key has not been released
            if (isRightReleased == false)
            {
                tankOne.moveTankRight();
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
            window.draw(gSprite);
            window.display();
        }
    }

    return 0;
}

void quit(bool OUTPUT_FEEDBACK, sf::Text quitText, sf::RenderWindow& window)
{
    // for debugging/feedback
    if(OUTPUT_FEEDBACK) std::cerr << "Game Closed\n";
    window.draw(quitText);
    window.display();
    sf::sleep(sf::seconds(0));
    window.close();
    exit(0);
}