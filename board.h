#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Gameboard
{
    public:
        Gameboard(const std::string& playerName, int initialScore);

        void increaseScore(int increaseBy);

        void draw(sf::RenderWindow& window);

    private:
        void updateScoreText();

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