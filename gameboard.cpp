#include "gameboard.h"

Gameboard::Gameboard(const std::string& playerName, int initialScore) : mPlayerName(playerName), mScore(initialScore)
{
    mFont.loadFromFile("assets/arial.ttf");
    mNameText.setFont(mFont);
    mNameText.setCharacterSize(24);
    mNameText.setFillColor(sf::Color::White);
    mNameText.setPosition(20, 20);
    mNameText.setString(playerName);
    mScoreText.setPosition(600, 20);
    updateScoreText();
    
    // "Level" text.
    mLevelText.setFont(mFont);
    mLevelText.setCharacterSize(24);
    mLevelText.setFillColor(sf::Color::White);
    mLevelText.setPosition(330, 20);
    mLevel = 0;
    updateLevelText();

    // "Close" text.
    mCloseText.setFont(mFont);
    mCloseText.setPosition(320, 400);
    mCloseText.setString("CLOSING...");
    mCloseText.setCharacterSize(36);
    mCloseText.setFillColor(sf::Color::White);

    // "Game Over" text.
    mGameOverText.setFont(mFont);
    mGameOverText.setPosition(350, 400);
    mGameOverText.setString("GAME OVER...");
    mGameOverText.setCharacterSize(36);
    mGameOverText.setFillColor(sf::Color::White);
}

void Gameboard::increaseScore(int increaseBy)
{
    mScore += increaseBy;
    updateScoreText();
}

void Gameboard::draw(sf::RenderWindow& window) const
{
    window.draw(mNameText);
    window.draw(mScoreText);
}

void Gameboard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mNameText, states);
    target.draw(mScoreText, states);
}

void Gameboard::drawAdditionalText(sf::RenderWindow& window, const sf::Text& additionalText)
{
    window.draw(additionalText);
}

sf::Text& Gameboard::getLevelText()
{
    return mLevelText;
}

sf::Text Gameboard::getPauseText()
{
    sf::Text pauseText;
    pauseText.setFont(mFont);
    pauseText.setCharacterSize(36);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(350, 350);
    pauseText.setString("PAUSE");
    return pauseText;
}

sf::Text Gameboard::getGameOverText()
{
    return mGameOverText;
}

sf::Text Gameboard::getCloseText()
{
    return mCloseText;
}

void Gameboard::updateScoreText()
{
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(24);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setString("Score: " + std::to_string(mScore));
}

void Gameboard::updateLevelText()
{
    mLevel++;
    mLevelText.setString("Level: " + std::to_string(mLevel)); // convert mLevel to string
}