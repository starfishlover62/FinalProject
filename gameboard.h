#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Gameboard : public sf::Drawable
{
    public:
        Gameboard(const std::string& playerName, int initialScore);
        sf::Text pauseScreen();
        void increaseScore(int increaseBy);
        void updateScoreText();
        void displayGameOverScreen();
        void displayPauseScreen();
        void displayQuitOverScreen();
        void displayLevel();
        void increaseLevel();
        void draw(sf::RenderWindow& window) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText);
    private:
        std::string mPlayerName;
        int mScore;
        int mLevel;
        sf::Font mFont;
        sf::Text mNameText;
        sf::Text mScoreText;
        sf::Image mPlayerSpaceshipImage;
        sf::Image mSpaceInvadersImage;
        sf::Image mEnemySpaceshipImage;
};

#endif
