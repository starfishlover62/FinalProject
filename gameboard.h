#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Gameboard
{
    public:
        Gameboard(const std::string& playerName, int initialScore);
        void increaseScore(int increaseBy);
        void draw(sf::RenderWindow& window);
        void updateScoreText();
        void displayGameOverScreen();
        void displayPauseScreen();
        void displayQuitOverScreen();

    private:

        std::string mPlayerName;
        int mScore;
        sf::Font mFont;
        sf::Text mNameText;
        sf::Text mScoreText;
        sf::Image mPlayerSpaceshipImage;
        sf::Image mSpaceInvadersImage;
        sf::Image mEnemySpaceshipImage;
};

#endif
