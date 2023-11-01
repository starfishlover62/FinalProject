#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "alien.h"
#include "squid.h"
#include "tank.h"
#include "playerName.h"
#include "board.h"

class playerSpaceship
{
    private:

    public:

};

class spaceInvader
{
    private:

    public:
    
};

class enemySpaceship
{
    private:

    public:
    
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Invaders");

    // PlayerName playerName;
    // playerName.setPlayerName(window);
    Gameboard gameboard("No Name", 0); // temp no name for player

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



    // debugging
    // std::cerr << playerName;

    // for(int i = 0; i < playerName[i] != '\0'; i++)
    // {
    //     std::cout << playerName[i];
    // }
        
    while (window.isOpen())
    {
        sf::Text text;
        text.setString("Hello, SFML!");
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (/*Destroy Enemy Tier 1, PTS += 2*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // TEST
                    gameboard.increaseScore(2);
                }
                else if (/*Destroy Enemy Tier 2, PTS += 5*/ event.mouseButton.button == sf::Mouse::Right)
                {
                    // increment score with left click
                    gameboard.increaseScore(5);
                }
                else if (/*Destroy Enemy Tier 3, PTS += 10*/ event.mouseButton.button == sf::Mouse::Middle)
                {
                    // increment score with left click
                    gameboard.increaseScore(10);
                }
                else if (/*Destroy Enemy Tier 4, PTS += 20*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(20);
                }
                else if (/*Destroy Enemy Tier 5, PTS += 50*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(50);
                }
                else if (/*Destroy Enemy SPACESHIP, PTS += 750*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(750);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                tankOne.moveTankRight();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                tankOne.moveTankLeft();
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
