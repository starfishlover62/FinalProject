
// Compile with:
// g++ main.cpp alien.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "alien.h"

class PlayerName
{
    public:
        void setPlayerName(sf::Window& window)
        {
            // mFont.loadFromFile("arial.ttf"); // don't know how to load font from c drive
            // mNameText.setFont(mFont);
            // mNameText.setString("");
            // mNameText.setCharacterSize(24); // Set the font size
            // mNameText.setFillColor(sf::Color::White); // Set the text color
            // mNameText.setPosition(20, 20); // Set the position of the text
            sf::Event event;
            while (window.pollEvent(event) && PlayerName.length())
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }   
                if (mEvent.type == sf::Event::TextEntered)
                {
                    std::cin >> PlayerName;
                }
            }
        }
        void displayPlayerName()
        {
            ;
        }

    private:
            std::string PlayerName;
            sf::Font mFont;
            sf::String mInput;
            sf::Text mPlayerText;
            sf::Event mEvent;
};

class Gameboard
{
    public:
        Gameboard(const std::string& playerName, int initialScore) : mPlayerName(playerName), mScore(initialScore)
        {

            mFont.loadFromFile("arial.ttf"); // don't know how to load font from c drive
            mNameText.setFont(mFont);
            mNameText.setCharacterSize(24);
            mNameText.setFillColor(sf::Color::White);
            mNameText.setPosition(20, 20);
            mNameText.setString("Player Name");

            updateScoreText();
            mScoreText.setPosition(600, 20);
        }

        void increaseScore(int increaseBy)
        {
            mScore += increaseBy;
            updateScoreText();
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(mNameText);
            window.draw(mScoreText);
        }

    private:
        void updateScoreText()
        {
            mScoreText.setFont(mFont);
            mScoreText.setCharacterSize(24);
            mScoreText.setFillColor(sf::Color::White);
            mScoreText.setString("Score: " + std::to_string(mScore));
        }

        std::string mPlayerName;
        int mScore;
        sf::Font mFont;
        sf::Text mNameText;
        sf::Text mScoreText;
        sf::Image mPlayerSpaceshipImage;
        sf::Image mSpaceInvadersImage;
        sf::Image mEnemySpaceshipImage;
};

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
    // prompt user to enter their name
    
    PlayerName playerName;
    playerName.setPlayerName(window);

    Gameboard gameboard("Player", 0);

    Squid squid1;

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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // TEST
                    gameboard.increaseScore(3);
                }
                else if (/*Destroy Enemy Tier 1, PTS += 5*/ event.mouseButton.button == sf::Mouse::Right)
                {
                    // increment score with left click
                    gameboard.increaseScore(5);
                }
                else if (/*Destroy Enemy Tier 2, PTS += 10*/ event.mouseButton.button == sf::Mouse::Middle)
                {
                    // increment score with left click
                    gameboard.increaseScore(10);
                }
                else if (/*Destroy Enemy Tier 3, PTS += 20*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(20);
                }
                else if (/*Destroy Enemy SPACESHIP, PTS += 150*/ event.mouseButton.button == sf::Mouse::Left)
                {
                    // increment score with left click
                    gameboard.increaseScore(150);
                }
            }
        }

        window.clear();
        gameboard.draw(window);
        squid1.draw(window);
        window.display();
    }

    return 0;
}
