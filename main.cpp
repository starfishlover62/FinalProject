#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "alien.h"
#include "squid.h"
#include "tank.h"

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

            mFont.loadFromFile("assets/arial.ttf"); // don't know how to load font from c drive
            mNameText.setFont(mFont);
            mNameText.setCharacterSize(24);
            mNameText.setFillColor(sf::Color::White);
            mNameText.setPosition(20, 20);
            mNameText.setString(playerName);

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
    // begin enter player name
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) // don't know how to load font from c drive
    {
        // Handle font loading error
        std::cerr << "Error loading font file." << std::endl;
        return -1;
    }

    sf::Text promptForName;
    promptForName.setString("Player Name: "); // text
    promptForName.setPosition(200, 300); // position
    promptForName.setFont(font);
    promptForName.setCharacterSize(24);
    promptForName.setFillColor(sf::Color::White);

    sf::Text startTyping;
    startTyping.setString("(Start Typing)"); // text
    startTyping.setPosition(375, 300); // position
    startTyping.setFont(font);
    startTyping.setCharacterSize(24);
    startTyping.setFillColor(sf::Color::White);

    sf::Text input; // user input
    input.setPosition(375, 300); // position
    input.setFont(font);
    input.setCharacterSize(24);
    input.setFillColor(sf::Color::White);

    std::string playerName;
    bool enteredName = false;
    bool enteredCharacter = false;

    while (window.isOpen() && !enteredName)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 13)
                    {
                        enteredName = true;
                    }
                    else if (event.text.unicode == 8 && playerName.size() > 0)
                    {
                        // handle backspace to erase characters
                        playerName.pop_back();
                    }
                    else
                    {
                        // handle regular key presses and add them to the inputText
                        enteredCharacter = true;
                        playerName += static_cast<char>(event.text.unicode);
                    }
                    input.setString(playerName);
                }
            }
        }

        window.clear();
        if(!enteredCharacter)
        {
            window.draw(startTyping);
        }
        window.draw(promptForName);
        window.draw(input);
        window.display();
    }
    // end enter player name


    Gameboard gameboard(playerName, 0);

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
    gTexture.loadFromFile("siground.png");
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
        gameboard.draw(window);
        for(int i = 0; i < Number_Of_Squids; i++)
        {
            window.draw(squidObjects[i]);
        }
        window.draw(tankOne);
        window.draw(gSprite);
        window.display();
    }

    return 0;
}
