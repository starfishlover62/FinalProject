#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Gameboard : public sf::Drawable
{
    public:
        Gameboard(const std::string& playerName, int initialScore);
        sf::Text& getLevelText();
        sf::Text getPauseText();
        sf::Text getGameOverText();
        sf::Text getCloseText();
        void increaseScore(int increaseBy);
        void updateScoreText();
        void updateLevelText();
        void draw(sf::RenderWindow& window) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText);

    private:
        std::string mPlayerName;
        int mScore;
        int mLevel;
        sf::Font mFont;

        sf::Text mPauseText;
        sf::Text mLevelText;
        sf::Text mNameText;
        sf::Text mScoreText;
        sf::Text mGameOverText;
        sf::Text mCloseText;

        sf::Image mPlayerSpaceshipImage;
        sf::Image mSpaceInvadersImage;
        sf::Image mEnemySpaceshipImage;
};

#endif
