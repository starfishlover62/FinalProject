#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Gameboard : public sf::Drawable
{
    public:
        Gameboard(const std::string& playerName, int initialScore);
        sf::Text getLivesText();
        sf::Text& getLevelText();
        sf::Text getPauseText();
        sf::Text getGameOverText();
        sf::Text getCloseText();
        sf::Text getRetryText();
        void increaseScore(int increaseBy);
        void updateScoreText();
        void updateLevelText();
        void draw(sf::RenderWindow& window) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText);
        void initializeText(sf::Text& text, float x, float y, const std::string& content, unsigned int size, sf::Color color);
        sf::Font loadFont();

    private:
        std::string mPlayerName;
        int mScore;
        int mLevel;
        sf::Font mFont;

        sf::Text mLives;
        sf::Text mPauseText;
        sf::Text mLevelText;
        sf::Text mNameText;
        sf::Text mScoreText;
        sf::Text mGameOverText;
        sf::Text mCloseText;
        sf::Text mRetryText;

        sf::Image mPlayerSpaceshipImage;
        sf::Image mSpaceInvadersImage;
        sf::Image mEnemySpaceshipImage;
};

#endif
